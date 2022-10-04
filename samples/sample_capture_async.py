"""Async capture sample."""
import asyncio
import datetime
from zivid import Application, Settings


async def _main():
    app = Application()
    # camera = app.connect_camera()
    camera1 = app.create_file_camera("test/test_data/FileCameraZividOne.zfc")
    camera2 = app.create_file_camera("test/test_data/FileCameraZividOne.zfc")

    settings = Settings()
    settings.acquisitions.append(Settings.Acquisition())
    settings.acquisitions[0].aperture = 5.6
    settings.acquisitions[0].exposure_time = datetime.timedelta(microseconds=100000)
    settings.processing.filters.outlier.removal.enabled = True
    settings.processing.filters.outlier.removal.threshold = 5.0

    print("Capture first!")
    frame_future1 = camera1.capture_async(settings)
    # print("Capture second!")
    # frame_future2 = camera2.capture_async(settings)
    print("Awaiting the first one!")
    frame = await frame_future1.inner()
    # print("Awaiting the second one!")
    # frame = await frame_future2.inner()
    print("Capture done!")
    frame.save("result.zdf")
    print("Frame saved!")



if __name__ == "__main__":
    asyncio.run(_main())
