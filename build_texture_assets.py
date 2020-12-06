#!/usr/bin/python3
import os
from shutil import copyfile

def BuildTextureFile(xmlPath, outputPath):
	execStr = "tools/ZAP2/ZAP2.out b -i %s -b assets/textures -o %s -gsf 1" % (xmlPath, outputPath)

	print(execStr)
	os.system(execStr)

	# Copy generated C file to parent folder...
	#fileName = os.path.basename(xmlPath)
	#dirPath = os.path.dirname(xmlPath)
	#copyfile(outputPath + "/" + fileName.replace(".xml", ".c"), outputPath + "/../" + fileName.replace(".xml", ".c"))


# Textures
# BuildTextureFile("assets/textures/xml/icon_item_24_static.xml", "assets/textures/icon_item_24_static")
# BuildTextureFile("assets/textures/xml/icon_item_dungeon_static.xml", "assets/textures/icon_item_dungeon_static")
# BuildTextureFile("assets/textures/xml/icon_item_field_static.xml", "assets/textures/icon_item_field_static")
# BuildTextureFile("assets/textures/xml/icon_item_gameover_static.xml", "assets/textures/icon_item_gameover_static")
# BuildTextureFile("assets/textures/xml/icon_item_nes_static.xml", "assets/textures/icon_item_nes_static")
BuildTextureFile("assets/textures/xml/icon_item_static.xml", "assets/textures/icon_item_static")