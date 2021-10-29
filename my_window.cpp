#include "header.h"
#include <cairomm/context.h>
#include <iostream>
#define SCALE 1.25
using namespace std;

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& My window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

//-----------------------------constructeur mywindow---------------------------------//

my_window::my_window()
{
    

    /*----------setup window-------------------------------*/
        set_title("Colons Game !");
        set_position(Gtk::WIN_POS_CENTER);
        set_default_size(1805, 1005); //+5 size of all the window for the border
        set_border_width(5);
        set_my_menu(); // method to set up the menu
    /*--------------setup window----------------*/
    
    
    /*---------butons box--------------*/
        button_house.add_label("Build a House");
        button_house.signal_clicked().connect(sigc::mem_fun(*this, &my_window::button_add_house));
        button_route.add_label("Build Route");
        button_route.signal_clicked().connect(sigc::mem_fun(*this, &my_window::button_add_route));
        // | //
        // v //
        buttons_Grid.set_row_spacing(10);
        buttons_Grid.set_column_spacing(10);
        buttons_Grid.attach(button_house,0,0,1,1);
        buttons_Grid.attach(button_route,0,1,1,1);
        
        // | //
        // v //
        action_buttons_frame.set_label("Action Buttons");
        action_buttons_frame.add(buttons_Grid);
        // | //
        // v //
        buttons_box.set_spacing(10);
        buttons_box.set_size_request(600,900);
        buttons_box.pack_start(action_buttons_frame,0,0);
        
        
    /*---------butons box--------------*/    
    
    /*---------board box---------------*/
        board_Frame.set_label("Game Board");
        board_Frame.add(dessin);    
        board_box.set_size_request(1000, 900); // (width,hight)
        board_box.add(board_Frame);
    /*---------board box---------------*/

    /*---------mainGrid-------------------------*/
        mainGrid.set_row_spacing(10);
        mainGrid.set_column_spacing(10);
        mainGrid.attach(buttons_box, 0, 1, 1, 1);
        mainGrid.attach(board_box, 1, 1, 1, 1);
        mainLayout.add(mainGrid);
        add(mainLayout);     // ajoute la grid à la fenetre
        show_all_children(); // afficher tous les grid inclus dans la fènete
    /*---------mainGrid-------------------------*/
}

//--------------------------------------------------------------//

void my_window::button_add_house()
{
    Gtk::MessageDialog d(*this, "Choose your house position ", true, Gtk::MESSAGE_OTHER);
    d.run();
    dessin.set_add_house_pressed(true);
    
}

//--------------------------------------------------------------//

void my_window::button_add_route()
{
    // alerte widjet
    Gtk::MessageDialog d(*this, "Choose two intersections to build a route ", true, Gtk::MESSAGE_OTHER);
    d.run();
    dessin.set_add_route_pressed(true);
    
    
}
//--------------------------------------------------------------//

void my_window::set_my_menu()
{
    mainLayout.pack_start(menuBar, Gtk::PACK_SHRINK);
    // Create the menu item files
    menuFiles.set_label("Files");
    menuBar.append(menuFiles);
    // Create a sub menu in files
    menuFiles.set_submenu(subMenuFiles);
    open.set_label("OPEN");
    subMenuFiles.append(open);
    close.set_label("CLOSE");
    subMenuFiles.append(close);
    subMenuFiles.append(hline); // Add a separator
    quit.set_label("QUIT");
    subMenuFiles.append(quit);
    // Create the menu item Edit
    menuEdit.set_label("Edit");
    menuBar.append(menuEdit);
    // ::: Create the event for MenuItem :::
    quit.signal_activate().connect(sigc::ptr_fun(&Gtk::Main::quit));
}