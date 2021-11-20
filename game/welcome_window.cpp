#include "../header.h"

AboutWindow::AboutWindow()
	{
    this->set_title("welcome to colons de catanes game");
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_default_size(500, 400); //+5 size of all the window for the border	
    set_border_width(5);

    lbl_.set_label("Colons de Catanes");
    button_start_new_win.add_label("new_win_test");
    button_start_new_win.signal_clicked().connect(sigc::mem_fun(*this, &AboutWindow::Open_New_Win_Clicked));
    grid.attach(lbl_,0,0,1,1);
    grid.attach(button_start_new_win,0,1,1,1);
    this->add(grid);
    this->show_all_children();
	};



void AboutWindow::Open_New_Win_Clicked()
{

    main_window = new my_window();
    /*
    
        all settings to mainwindow
    
    */

    main_window->show();
    button_start_new_win.hide();
    
}