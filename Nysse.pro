TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
	Game \
	GameTest

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
