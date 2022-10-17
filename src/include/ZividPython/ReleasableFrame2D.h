#pragma once

#include <Zivid/Frame2D.h>
#include <Zivid/Settings2D.h>

#include <ZividPython/Releasable.h>
#include <ZividPython/ReleasableImage.h>
#include <ZividPython/Wrappers.h>

#include <future>

namespace ZividPython
{
    class ReleasableFrame2D : public Releasable<Zivid::Frame2D>
    {
    public:
        using Releasable<Zivid::Frame2D>::Releasable;

        ZIVID_PYTHON_FORWARD_0_ARGS_WRAP_RETURN(ReleasableImageRGBA, imageRGBA)
        ZIVID_PYTHON_FORWARD_0_ARGS(settings)
        ZIVID_PYTHON_FORWARD_0_ARGS(state)
        ZIVID_PYTHON_FORWARD_0_ARGS(info)
    };

    class FutureFrame2D
    {
    public:
        FutureFrame2D(std::future<ReleasableFrame2D> frame)
            : m_frame(std::move(frame))
        {}

        ReleasableFrame2D get()
        {
            return m_frame.get();
        }

        bool isReady()
        {
            return m_frame.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
        }

    private:
        std::future<ReleasableFrame2D> m_frame;
    };

    void wrapClass(pybind11::class_<ReleasableFrame2D> pyClass);
} // namespace ZividPython
