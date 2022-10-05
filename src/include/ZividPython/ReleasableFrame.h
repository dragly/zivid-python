#pragma once

#include <Zivid/Frame.h>
#include <ZividPython/Releasable.h>
#include <ZividPython/ReleasablePointCloud.h>
#include <ZividPython/Wrappers.h>

#include <future>
#include <pybind11/pybind11.h>

namespace ZividPython
{
    class ReleasableFrame : public Releasable<Zivid::Frame>
    {
    public:
        using Releasable<Zivid::Frame>::Releasable;

        ZIVID_PYTHON_FORWARD_1_ARGS(save, const std::string &, fileName)
        ZIVID_PYTHON_FORWARD_1_ARGS(load, const std::string &, fileName)
        ZIVID_PYTHON_FORWARD_0_ARGS_WRAP_RETURN(ReleasablePointCloud, pointCloud)
        ZIVID_PYTHON_FORWARD_0_ARGS(settings)
        ZIVID_PYTHON_FORWARD_0_ARGS(state)
        ZIVID_PYTHON_FORWARD_0_ARGS(info)
        ZIVID_PYTHON_FORWARD_0_ARGS(cameraInfo)
    };

    class FutureFrame
    {
    public:
        FutureFrame(std::future<ReleasableFrame> frame)
            : m_frame(std::move(frame))
        {}

        //pybind11::object await()
        //{
        //pybind11::object loop = pybind11::module_::import("asyncio.events").attr("get_event_loop")();
        //pybind11::object f = loop.attr("create_future")();
        //f.attr("set_result")(m_frame.get());
        //return f.attr("__await__")();
        //}

        ReleasableFrame get()
        {
            return m_frame.get();
        }

        bool isReady()
        {
            return m_frame.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
        }

    private:
        std::future<ReleasableFrame> m_frame;
    };

    void wrapClass(pybind11::class_<ReleasableFrame> pyClass);
} // namespace ZividPython
