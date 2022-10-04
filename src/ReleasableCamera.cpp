#include "include/ZividPython/ReleasableFrame.h"
#include <Zivid/Settings.h>
#include <ZividPython/ReleasableCamera.h>
#include <ZividPython/ReleasableFrame.h>

#include <pybind11/pybind11.h>

#include <future>
#include <variant>
#include <vector>

namespace py = pybind11;

namespace ZividPython
{
    void wrapClass(pybind11::class_<ReleasableCamera> pyClass)
    {
        pyClass.def(py::init())
            .def(py::self == py::self) // NOLINT
            .def(py::self != py::self) // NOLINT
            .def("disconnect", &ReleasableCamera::disconnect)
            .def("connect", &ReleasableCamera::connect)
            .def("capture", py::overload_cast<const Zivid::Settings &>(&ReleasableCamera::capture), py::arg("settings"))
            .def("capture",
                 py::overload_cast<const Zivid::Settings2D &>(&ReleasableCamera::capture),
                 py::arg("settings_2d"))
            .def("capture_async",
                 [](const ReleasableCamera &camera, const Zivid::Settings &settings) {
                     auto cam = camera;
                     std::cout << "Capture async!" << std::endl;
                     py::object loop = py::module_::import("asyncio.events").attr("get_event_loop")();
                     py::object f = loop.attr("create_future")();
                     auto result = std::async(std::launch::async, [=]() mutable {
                         std::cout << "Capture async starting!" << std::endl;
                         cam.capture(settings);
                         //f.attr("set_result")(cam.capture(settings));
                         std::cout << "Capture async done!" << std::endl;
                     });
                     std::cout << "Returning!" << std::endl;
                     return FutureFrame((f), std::move(result));
                 })
            .def_property_readonly("state", &ReleasableCamera::state)
            .def_property_readonly("info", &ReleasableCamera::info)
            .def("write_user_data", &ReleasableCamera::writeUserData)
            .def_property_readonly("user_data", &ReleasableCamera::userData);
    }
} // namespace ZividPython
