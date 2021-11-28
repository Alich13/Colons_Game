#include "../header.h"

AboutWindow::AboutWindow()
	{
    this->set_title("welcome to colons de catanes game");
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_default_size(500, 400); //+5 size of all the window for the border	
    set_border_width(5);
    /*--------------logo------------------------*/
    logo = Gdk::Pixbuf::create_from_file("data/logo.png");
    logo = logo->scale_simple((logo->get_width()) * 0.5,(logo->get_height()) * 0.4, Gdk::INTERP_BILINEAR);
    Logo.set(logo);
    /*------------------------------------------*/
    grid.set_column_spacing(20);
    grid.set_row_spacing(20);
    grid.set_margin_left(100);

    /*-------------combobox----------------------------*/
    
    //Fill the combo:
    c.append("something");
    c.append("something else");
    c.append("something or other");
    c.set_active(1);

    lbl_.set_label("Colons de Catanes");
    button_start_new_win.add_label("Start Game");
    button_start_new_win.signal_clicked().connect(sigc::mem_fun(*this, &AboutWindow::Open_New_Win_Clicked));
    grid.attach(lbl_,0,0,1,1);
    grid.attach(c,0,1,1,1);
    grid.attach(button_start_new_win,0,2,1,1);
    mainLayout.pack_start(Logo);
    mainLayout.pack_start(grid);
    this->add(mainLayout);
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