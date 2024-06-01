import cairosvg
from io import BytesIO
from PIL import Image

data = cairosvg.svg2png(url='before.svg')
before = Image.open(BytesIO(data))
before.show()
