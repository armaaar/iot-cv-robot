import io
import time
import picamera
from .base_camera import BaseCamera
from PIL import Image


class Camera(BaseCamera):
    @staticmethod
    def frames():
        with picamera.PiCamera() as camera:
            # let camera warm up
            camera.resolution = (720, 720)
            camera.framerate = 10
            time.sleep(2)

            stream = io.BytesIO()
            for _ in camera.capture_continuous(stream, 'jpeg',
                                                 use_video_port=True):
                # return current frame
                stream.seek(0)
                #a
                #a = stream.read()
                
                yield stream.read()

                # reset stream for next frame
                stream.seek(0)
                stream.truncate()
