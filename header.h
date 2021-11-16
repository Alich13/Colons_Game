#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/alignment.h>
#include "data_structures.h" //import the costumized data structure we will use in Board class


/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& player   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
class Player
{
public:
	States id;
	//------------------methodes---------------------------------------//
	Player(States N_id,string N_nickname);
	int count_ressources(Ressouces ressource_we_looking_for); /////!!!!
	int get_player_INT_id();
	States get_player_STATE_id();
	string get_name();

private:
	string Nickname;
	int total_points = 0;
	vector<Ressouces> ressources = {};
	
	
};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&  Board  &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief
 * This class  contains the board elements intersections , tuiles, routes
 * these elements themselves are also classes  that contain all informations like
 * cordonates of elements ,methodes to check .
 * for example the states of different elements
 * This class uses internally the classes T_map and I_map "from data_stucture.h"
 */
class Board
{
public:
	Board();
	// I_map board_map;
	T_map tuile_map;
	I_map intersection_map;

private:
};

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Dessin   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief
 * This class represents the actual drawing (le dessin ) which will be included in boardBOX
 * all elements from Board will be printed here as well as all the interaction via eventbox
 * that allows us for example to place new houses or routes
 */
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
	void drawBoard(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_intersection_map(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawVingnette(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawRoute(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawPossibleRoute(const Cairo::RefPtr<Cairo::Context> &cr);
	void drawHouse(const Cairo::RefPtr<Cairo::Context> &cr);
	void setActivePlayer(Player* current_player);
	void ReafficheDessin();

protected:
	bool on_button_press_event(GdkEventButton *event);			 // function handles mouse events
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &); // make the drawings

private:
	Board board;
	// set sub maps (tuiles map  et intersection map)
	T_map tuile_map = board.tuile_map;
	I_map route_map = board.intersection_map;
	Player* active_player; // a pointer to the active player  

	int x1, x2, y1, y2; // cordonates of points
	int cord_x = 0;
	int cord_y = 0;		  // cord to be rendred in label
	int board_x, board_y; // top right x y cordonate inside the box
	int board_width, board_height;

	bool firstclick, secondclick;
	bool add_route_pressed = false;
	bool add_house_pressed = false; // bool var telling if the button build route is pressed or not

	std::vector<int> X, Y, vx1, vy1, vx2, vy2;
	Glib::RefPtr<Gdk::Pixbuf> pic_board, pic2, vigniette ,construction;
};


/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Game  window   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/
/**
 * @brief
 * This class represent the main window of the game :
 * it contains :
 * 			-/ game board (drawing)
 * 			-/ button box
 * 			-/ dé
 */
class my_window : public Gtk::Window
{
public:
	my_window();
	virtual ~my_window(){};
	void button_add_house();
	void button_add_path();
	void button_add_route();
	void next_turn();

	//-------------------
	void set_player_list(); // this methode will be called from main to set the number of player at the begining of the game
							// my_window.set_player_list()

protected:
	
	Dessin dessin;

	// for test
		Player P1 = Player(States::p1,"ALi");
		Player P2 = Player(States::p2,"Louai");
		Player P3 = Player(States::p3,"jalil");
	//
	
	Gtk::VBox mainLayout, board_box, buttons_box;
	Gtk::Label player_turn_label;
	Gtk::Frame board_Frame, action_buttons_frame;
	Gtk::HButtonBox buttons_Hbox;
	Gtk::Grid mainGrid, buttons_Grid;
	Gtk::Button button_house, button_route ,button_next_turn;
	Gtk::MenuBar menuBar;
	Gtk::MenuItem menuFiles;
	Gtk::Menu subMenuFiles;
	Gtk::MenuItem open, close, quit;
	Gtk::SeparatorMenuItem hline;
	Gtk::MenuItem menuEdit;

private:
	void set_my_menu();
	vector<Player> player_list={P1,P2,P3} ;
	vector<Player>::iterator current_player_itr = player_list.begin(); 
};

#endif // GTKMM_EXAMPLE_MYAREA_H
