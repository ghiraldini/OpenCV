from SimpleCV import *
import time

def main():
	cam = Camera()

	# Capture Image from camera
	img = cam.getImage()
	img.show()

	time.sleep(1)

	# crop	
	crop = img.crop(520,320,120,200)
	crop.show()
	
	time.sleep(2)

	# remove color
	couch = cam.getImage()
	brown = couch.colorDistance(Color.BEIGE)
	brown.show()
	
	time.sleep(3)
	
	only_brown = img - brown
	only_brown.show()
	
	# outputs RGB color of image
	only_brown.meanColor()
	time.sleep(2)
	
	lenna = cam.getImage()
	segment = HaarCascade("face.xml")
	autoface = lenna.findHaarFeatures(segment)
	if ( autoface is not None ):
		face = autoface[-1].crop()
		face.show()

	face.save("/home/lgr/cam_code/face.jpg")
	time.sleep(4)

	invert = face.invert()
	invert.show()
	time.sleep(2)
	
	

def motion_detect():
	cam = Camera()
	threshold = 3.0 # if mean exceeds this amount do something

	while True:
		previous = cam.getImage() #grab a frame
		time.sleep(0.25) #wait for half a second
		current = cam.getImage() #grab another frame
		diff = current - previous
		matrix = diff.getNumpy()
		mean = matrix.mean()

		diff.show()

		if mean >= threshold:
		        print "Motion Detected"

main()
#motion_detect()





# COLORS
#Color.AQUAMARINE        Color.FORESTGREEN       Color.LIME              Color.ROYALBLUE         Color.YELLOW
#Color.AZURE             Color.FUCHSIA           Color.MAROON            Color.SALMON            Color.colorlist
#Color.BACKGROUND        Color.GOLD              Color.MAYBE_BACKGROUND  Color.SILVER            Color.getAverageRGB
#Color.BEIGE             Color.GRAY              Color.MAYBE_FOREGROUND  Color.TAN               Color.getHueFromBGR
#Color.BLACK             Color.GREEN             Color.MEDIUMBLUE        Color.TEAL              Color.getHueFromRGB
#Color.BLUE              Color.HOTPINK           Color.NAVYBLUE          Color.VIOLET            Color.getLightness
#Color.CHARCOAL          Color.INDIGO            Color.OLIVE             Color.WATERSHED_BG      Color.getLuminosity
#Color.CRIMSON           Color.IVORY             Color.ORANGE            Color.WATERSHED_FG      Color.getRandom
#Color.CYAN              Color.KHAKI             Color.PLUM              Color.WATERSHED_UNSURE  Color.hsv
#Color.DEFAULT           Color.LEGO_BLUE         Color.PUCE              Color.WHEAT             Color.hueToBGR
#Color.FOREGROUND        Color.LEGO_ORANGE       Color.RED               Color.WHITE             Color.hueToRGB

