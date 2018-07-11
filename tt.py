from PIL import Image
img = Image.open('/home/pi/Pics/1.jpg')
img.show()
img.save('brick-house-gs','png')
