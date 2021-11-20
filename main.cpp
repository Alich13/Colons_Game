#include "header.h"
#include <iostream>
#include <gtkmm.h>
#include <gtkmm/window.h>


int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv);

  AboutWindow A;

  app->run(A);

  return 0 ;
}

/*

*/

