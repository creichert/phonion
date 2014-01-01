# -*- coding: UTF-8 -*-

##############################################################################
#                                                                            #
# Copyright (c) 2007-2010 Bernd Kreuss <prof7bit@gmail.com>                  #
#                                                                            #
# Translation file for TorChat                                               #
#                                                                            #
##############################################################################

LANGUAGE_CODE = u"nl"
LANGUAGE_NAME = u"Nederlands"
LANGUAGE_NAME_ENGLISH = u"Dutch"
TRANSLATOR_NAMES = [u"2by3"]

#buttons
BTN_CANCEL = u"Annuleren"
BTN_OK = u"Ok"
BTN_SAVE_AS = u"Opslaan als..."
BTN_CLOSE = u"Sluiten"

#status
ST_AVAILABLE = u"Aanwezig"
ST_AWAY = u"Afwezig"
ST_EXTENDED_AWAY = u"Langdurig afwezig"
ST_OFFLINE = u"Offline"

#TaskbarMenu
MTB_SHOW_HIDE_TORCHAT = u"Toon/Verberg TorChat"
MTB_QUIT = u"Sluiten"

#popup menu
MPOP_CHAT = u"Chat..."
MPOP_SEND_FILE = u"Verzend bestand..."
MPOP_EDIT_CONTACT = u"Bewerk contactpersoon..."
MPOP_DELETE_CONTACT = u"Verwijder contact..."
MPOP_SHOW_OFFLINE_MESSAGES = u"Toon Offline berichten in wacht"
MPOP_CLEAR_OFFLINE_MESSAGES = u"Schoon Offline berichten in wacht"
# MPOP_ACTIVATE_LOG = u"Activate logging to file"
# MPOP_STOP_LOG = u"Stop logging"
# MPOP_DELETE_EXISTING_LOG = u"Delete existing log file"
# MPOP_DELETE_AND_STOP_LOG = u"Delete log and stop logging"
MPOP_ADD_CONTACT = u"Contactpersoon toevoegen..."
MPOP_ABOUT = u"Over TorChat"
MPOP_ASK_AUTHOR = u"Vraag %s..."
# MPOP_SETTINGS = u"Settings..."
# MPOP_EDIT_MY_PROFILE = u"Edit my profile..."

# #chat window popup menu
# CPOP_COPY = u"Copy"

#confirm delete message box
D_CONFIRM_DELETE_TITLE = u"Bevestig verwijderen"
D_CONFIRM_DELETE_MESSAGE = u"Weet u zeker dat u deze contactpersoon wilt verwijderen?\n(%s %s)"

#warning about log
D_LOG_WARNING_TITLE = u"TorChat: Logboek ingeschakeld"
D_LOG_WARNING_MESSAGE = u"Logging naar bestand is geactiveerd!\n\nLog bestand: %s\n\nVergeet niet het logbestand te verwijderen na het debuggen, deze kan gevoellige informatie bevatten"

# #warning about used port
# D_WARN_USED_PORT_TITLE = u"TorChat: Port already in use"
# D_WARN_USED_PORT_MESSAGE = u"Something, probably another TorChat instance, is already listening at %s:%s. You must create another profile using different ports to be able to start TorChat a second time."

#warnig about unread messages
D_WARN_UNREAD_TITLE = u"TorChat: Ongelezen berichten"
D_WARN_UNREAD_MESSAGE = u"Er zijn ongelezen berichten.\nDeze zullen verloren gaan!\n\nWeet u zeker dat u TorChat wilt sluiten?"

#warning about offline buddy
# D_WARN_BUDDY_OFFLINE_TITLE = u"TorChat: Buddy is offline"
# D_WARN_BUDDY_OFFLINE_MESSAGE = u"This operation is not possible with offline buddies"

#warning about multiple files
# D_WARN_FILE_ONLY_ONE_TITLE = u"TorChat: Multiple files"
# D_WARN_FILE_ONLY_ONE_MESSAGE = u"You may not start multiple file transfers with one operation. Start the transfers individually or send a zip-file instead"

# #warning about file save error
# D_WARN_FILE_SAVE_ERROR_TITLE = u"TorChat: Error saving file"
# D_WARN_FILE_SAVE_ERROR_MESSAGE = u"The file '%s' could not be created.\n\n%s"

# #warning about file already exists
# D_WARN_FILE_ALREADY_EXISTS_TITLE = u"TorChat: File exists"
# D_WARN_FILE_ALREADY_EXISTS_MESSAGE = u"The file '%s' already exists.\nOverwrite it?"

#dialog: add/edit contact
DEC_TITLE_ADD = u"Contactpersoon toevoegen"
DEC_TITLE_EDIT = u"Bewerk contactpersoon"
DEC_TORCHAT_ID = u"TorChat ID"
DEC_DISPLAY_NAME = u"Weergave naam"
DEC_INTRODUCTION = u"Introductie"
DEC_MSG_16_CHARACTERS = u"Het adres dient 16 karakters lang te zijn, niet %i."
DEC_MSG_ONLY_ALPANUM = u"Het adres kan alleen cijfers en kleine letters bevatten."
DEC_MSG_ALREADY_ON_LIST = u"%s staat al in uw lijst."

# #dialog: edit my profile
# DEP_TITLE = u"Edit my profile"
# DEP_NAME = u"Name"
# DEP_TEXT = u"Text"
# DEP_SET_AVATAR = u"Set Avatar"
# DEP_REMOVE_AVATAR = u"Remove Avatar"
# DEP_AVATAR_SELECT_PNG = u"Select .PNG file to use as your avatar (will be scaled to 64*64, may contain transparency)"
# DEP_PNG_FILES = u"PNG files"
# DEP_ALL_FILES = u"All files"
# DEP_WARN_TITLE = u"Avatar selection not possible"
# DEP_WARN_IS_ALREADY = u"This is already the current avatar"
# DEP_WARN_MUST_BE_PNG = u"The avatar must be a .png file"

#file transfer window
# DFT_FILE_OPEN_TITLE = u"Send file to %s"
# DFT_FILE_SAVE_TITLE = u"Save file from %s"
DFT_SEND = u"Verzenden %s\nnaar %s\n%04.1f%% (%i van %i bytes)"
DFT_RECEIVE = u"Ontvangen %s\nvan %s\n%04.1f%% (%i van %i bytes)"
# DFT_WAITING = u"waiting for connection"
# DFT_STARTING = u"starting transfer"
# DFT_ABORTED = u"transfer aborted"
# DFT_COMPLETE = u"transfer complete"
# DFT_ERROR = u"error"

# #settings dialaog
# DSET_TITLE = u"TorChat configuration"
# DSET_NET_TITLE = u"Network"
# DSET_NET_ACTIVE = u"active"
# DSET_NET_INACTIVE = u"inactive"
# DSET_NET_TOR_ADDRESS = u"Tor proxy address"
# DSET_NET_TOR_SOCKS = u"Socks port"
# DSET_NET_TOR_CONTROL = u"Control port"
# DSET_NET_OWN_HOSTNAME = u"Own TorChat-ID"
# DSET_NET_LISTEN_INTERFACE = u"Listen interface"
# DSET_NET_LISTEN_PORT = u"Listen port"
# DSET_GUI_TITLE = u"User interface"
# DSET_GUI_LANGUAGE = u"Language"
# DSET_GUI_OPEN_MAIN_HIDDEN = u"Start with minimized main window"
# DSET_GUI_OPEN_CHAT_HIDDEN = u"Don't automatically open new windows"
# DSET_GUI_NOTIFICATION_POPUP = u"Notification pop-up"
# DSET_GUI_NOTIFICATION_METHOD = u"Notification method"
# DSET_GUI_FLASH_WINDOW = u"Flash window title on new message"
# DSET_MISC_TITLE = u"Misc"
# DSET_MISC_TEMP_IN_DATA = u"Store temporary files inside data directory"
# DSET_MISC_TEMP_CUSTOM_DIR = u"Temporary directory (leave empty for OS-default)"

#notices in the chat window (those in square brackets)
NOTICE_DELAYED_MSG_WAITING = u"vertraagde berichten, wachtend om verzonden te worden"
NOTICE_DELAYED_MSG_SENT = u"vertraagde berichten zijn verzonden"
NOTICE_DELAYED = u"vertraagd"

# #messagebox for offline messages
# MSG_OFFLINE_TITLE = u"TorChat: queued messages"
# MSG_OFFLINE_EMPTY = u"there are no (more) queued messages for %s"
# MSG_OFFLINE_QUEUED = u"queued offline messages for %s:\n\n%s"

# #buddy list mouse hover popup
# BPOP_BUDDY_IS_OFFLINE = u"Buddy is offline"
# BPOP_CONNECTED_AWAITING_RETURN_CONN = u"Connected, awaiting return connection..."
# BPOP_CLIENT_SOFTWARE = u"Client: %s %s"

# #logging of conversations to file
# LOG_HEADER = u"This log file is not signed and has no cogency of proof"
# LOG_STARTED = u"Logging started"
# LOG_STOPPED = u"Logging stopped"
# LOG_DELETED = u"Log files have been deleted"
# LOG_IS_ACTIVATED = u"Logging to file is activated:\n%s"
# LOG_IS_STOPPED_OLD_LOG_FOUND = u"Logging is stopped but old log file still exists:\n%s"

#about box
ABOUT_TITLE = u"Over TorChat"
ABOUT_TEXT = u"""TorChat %(version)s (svn: r%(svn)s)
  %(copyright)s

Translations:
  %(translators)s

Runtime environment:
  Python: %(python)s
  wx: %(wx)s

TorChat is free software: you can redistribute it and/or \
modify it under the terms of the GNU General Public \
License as published by the Free Software Foundation, \
either version 3 of the License, or (at your option) \
any later version.

TorChat is distributed in the hope that it will be useful, \
but WITHOUT ANY WARRANTY; without even the implied \
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. \
See the GNU General Public License for more details.

*

And now for something completely different:

If you happen to run a software company near Hannover, Germany and \
are in need of a new coder, feel free to regard this little program \
as my application documents and drop me a mail with your answer.
"""