MAJOR = 1
MINOR = 0
COMPANY = FivCorp
DESCRIPTION = Description
APP_NAME = $$join(TARGET)
VERSION_HEADER = ../$$APP_NAME/details.rc

versiontarget.target = $$VERSION_HEADER
versiontarget.commands = ../version-build-desktop/release/version.exe $$MAJOR $$MINOR $$COMPANY $$DESCRIPTION $$APP_NAME $$VERSION_HEADER
versiontarget.depends = FORCE

PRE_TARGETDEPS += $$VERSION_HEADER
QMAKE_EXTRA_TARGETS += versiontarget

win32:RC_FILE = details.rc

SOURCES += main.cpp