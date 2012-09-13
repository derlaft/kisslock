/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include "kisslock.h"

int main() {
  Display *display; 
  
  display = XOpenDisplay(NULL);
  if (display == NULL) {
    printf("Cant open display\n");
    return 1;
  }
  
  XGrabServer(display);
  XFlush(display);
  
  int keyCode = XKeysymToKeycode(display, KEY);

  Window root = XDefaultRootWindow(display); 
  XGrabKey(display, keyCode, MOD, root, False, GrabModeAsync, GrabModeAsync);
  
  XSelectInput(display, root, KeyPressMask);
  
  int shouldQuit = 0;
  XEvent event;
  
  system("vbetool dpms off");
  while (!shouldQuit) {
    XNextEvent(display, &event);
    switch(event.type) {
      case KeyPress:
        XUngrabKey(display, keyCode, 0, root);
        shouldQuit = 1;
        system("vbetool dpms on");
        break;
    }
  }

  XUngrabServer(display);
  
  XCloseDisplay(display);
  return 0;
}
