#include "header.h"
#include <iostream>
#include <gtkmm.h>
#include <gtkmm/window.h>


int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv);
  
  Welcome_Window W;
  app->run(W);

  return 0 ;
}

/*

*/

