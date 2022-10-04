"""Async capture sample."""
import asyncio
import datetime
from zivid import Application, Settings


async def _main():
    app = Application()
    camera1 = app.connect_camera()
    camera2 = app.connect_camera()
    camera3 = app.connect_camera()
    # camera2 = app.create_file_camera("test/test_data/FileCameraZividOne.zfc")
    # camera3 = app.create_file_camera("test/test_data/FileCameraZividOne.zfc")

    settings = Settings()
    settings.acquisitions.append(Settings.Acquisition())
    settings.acquisitions[0].aperture = 5.6
    settings.acquisitions[0].exposure_time = datetime.timedelta(microseconds=100000)
    settings.processing.filters.outlier.removal.enabled = True
    settings.processing.filters.outlier.removal.threshold = 5.0

    print("Capture first!")
    frame_future1 = camera1.capture_async(settings)
    print("Capture second!")
    frame_future2 = camera2.capture_async(settings)
    print("Capture second!")
    frame_future3 = camera3.capture_async(settings)
    print("Awaiting them all!")
    frame1, frame2, frame3 = await asyncio.gather(
        frame_future1,
        frame_future2,
        frame_future3
    )
    print("Captures done!")
    frame1.save("result.zdf")
    frame2.save("result.zdf")
    frame3.save("result.zdf")
    print("Frames saved!")



if __name__ == "__main__":
    asyncio.run(_main())
