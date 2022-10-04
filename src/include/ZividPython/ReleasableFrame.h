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
        FutureFrame(pybind11::object pyFuture, std::future<void> frame)
            : m_pyFuture(std::move(pyFuture))
            , m_frame(std::move(frame))
        {}

        pybind11::object await()
        {
            return m_pyFuture;
        }

    private:
        pybind11::object m_pyFuture;
        std::future<void> m_frame;
    };

    void wrapClass(pybind11::class_<ReleasableFrame> pyClass);
} // namespace ZividPython
