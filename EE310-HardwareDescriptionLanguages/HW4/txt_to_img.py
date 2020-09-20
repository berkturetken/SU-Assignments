from PIL import Image
import numpy as np

imsize = 256

# Python code for list of 256x256 pixels to 256x256 image 
# Input: 8-bit pixels as string
# Output: 8-bit grayscale image

# How data is stored in txt?
"""
Txt File
|Row 1 |
|Row 2 |
  ..
  ..
|Row127|
|Row256|
"""

# Read data from txt 
with open('baboon.txt', 'r') as f:
    pixels = f.read().splitlines()

# Convert string pixels to int
for i,x in enumerate(pixels):
    pixels[i] = int(x,2)

# Convert the pixels into an array using numpy
array = np.array(pixels, dtype=np.uint8)

# Convert array into 8-bit 256x256 graysacle image
image_out = Image.new('L',(imsize,imsize))
image_out.putdata(array)

# Save the image
image_out.save('baboon_r.png')


