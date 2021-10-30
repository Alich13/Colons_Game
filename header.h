#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/alignment.h>
#include <string>			 // for string class
#include "data_structures.h" //import data structure we will use in Board class
using namespace std;

enum class Ressouces {ble,bois,moutons,argile,desert,mouton,pierre};
enum class States {empty,p1,p2,p3,p4,p5,p6};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Dessin   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
class Dessin : public Gtk::DrawingArea
{
public:
	Dessin();
	//~Dessin();

	// set up //

	void set_add_route_pressed(bool pressed) { this->add_route_pressed = pressed; };
	void set_add_house_pressed(bool pressed) { this->add_house_pressed = pressed; };
	void set_rendred_cord(int cord_x, int cord_y)
	{
		this->cord_x = cord_x;
		this->cord_y = cord_y;
	};

	// get_attributes //
	void affiche_rendred_cord();

	// events //
	void updateRoute(GdkEventButton *event);
	void updateHouse(GdkEventButton *event);

	// Draw Functions //
	void drawRoute(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawHouse(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawBoard(const Cairo::RefPtr<Cairo::Context> &cr);

	void ReafficheDessin();

protected:
	bool on_button_press_event(GdkEventButton *event);			 // function handles mouse events
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &); // make the drawings

private:
	int x1, x2, y1, y2; // cordonates of points
	int cord_x = 0;
	int cord_y = 0;		  // cord to be rendred in label
	int board_x, board_y; // top right x y cordonate inside the box
	int board_width, board_height;
	bool firstclick, secondclick;
	bool add_route_pressed = false;
	bool add_house_pressed = false; // bool var telling if the button build route is pressed or not
	std::vector<int> X, Y, vx1, vy1, vx2, vy2;
	Glib::RefPtr<Gdk::Pixbuf> pic_board, pic2, display;
};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& My window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

class my_window : public Gtk::Window
{
public:
	my_window();
	virtual ~my_window(){};
	void button_add_house();
	void button_add_path();
	void button_add_route();

protected:
	Dessin dessin;
	Gtk::VBox mainLayout, board_box, buttons_box;
	Gtk::Label m_label;
	Gtk::Frame board_Frame, action_buttons_frame;
	Gtk::HButtonBox buttons_Hbox;
	Gtk::Grid mainGrid, buttons_Grid;
	Gtk::Button button_house, button_route;
	Gtk::MenuBar menuBar;
	Gtk::MenuItem menuFiles;
	Gtk::Menu subMenuFiles;
	Gtk::MenuItem open, close, quit;
	Gtk::SeparatorMenuItem hline;
	Gtk::MenuItem menuEdit;

private:
	void set_my_menu();
};

//--------------------------------------------------------------//
class De
{
public:
	De();

protected:
private:
};
//--------------------------------------------------------------//

class tuile
{

public:
	tuile();
	tuile(int tuile_id ,int x , int y ,Ressouces ressource) 
	{
		this->tuile_id=tuile_id;
		this->x=x; this->y=y;
		this->ressource=ressource;	
		/*this->num_dé_random */
	}
	void set_num_de();
protected:
private:
	int tuile_id;
	int x, y; // cordonates
	Ressouces ressource ;
	int num_de;
};

//--------------------------------------------------------------//

class intersection
{

public:
	intersection();

protected:
private:
	int x, y;
	States state ;	// state of the intersection (empty or  player id)
	std::array<tuile, 3> adj_ressource; // list of maximum 3 tuiles
};

//--------------------------------------------------------------//

class Board
{

public:
	Board(); //!!!! where we acctually set the board (ie) set board_map and tuiles_map  // 

	bool check_route_exist(int x ,int y);
	bool check_construction_exist(int x ,int y);
	bool check_possible_route(int x , int y);
	bool check_possible_construction(int x , int y);

	void update_board();

private:	
	I_map board_map;

	//---------functions used by the constructor-------//
	void fill_intersection_map();
	//------------------------------------------------//
};

//--------------------------------------------------------------//

#endif // GTKMM_EXAMPLE_MYAREA_H
