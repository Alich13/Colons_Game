#include "../header.h"
#include <cairomm/context.h>
#include <iostream>
#include <string> // for string class
#define SCALE 1.25
using namespace std;

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Dessin   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

//---------------------------------- constructor----------------------------------//

Dessin::Dessin()
{
	//  Load images
	pic_board = Gdk::Pixbuf::create_from_file("data/Board_org.png");
	pic2 = Gdk::Pixbuf::create_from_file("data/scarabine.png");
	pic_board = pic_board->scale_simple((pic_board->get_height()) * 0.20, (pic_board->get_width()) * 0.20, Gdk::INTERP_BILINEAR); // scale image
	pic2 = pic2->scale_simple((pic2->get_height()) * 0.10, (pic2->get_width()) * 0.25, Gdk::INTERP_BILINEAR);					  // scale image
	// Set masks for mouse events
	add_events(Gdk::BUTTON_PRESS_MASK);
	// setting attributes value

	board_x = 100;		// top right x cordonate inside the box
	board_y = 50;		// top right y cordonate inside the box
	board_width = 1000; // same as the size of the box !!!!!!!!!!!
	board_height = 900; // same as the size of the box !!!!!!!!!!!!!
}

//----------------------------------On draw----------------------------------//
/**
 * @brief
 * this fuction makes  all the drawing  in our board box
 * overloading (surcharge ) this fuction is continually making the drawing and
 * changes when a modification is made
 * @param cr cursor variable
 * @return true
 * @return false
 */
bool Dessin::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{

	/*---------------test to print mouse cordonates--------*/
	affiche_rendred_cord();
	/*---------------test to print mouse cordonates--------*/

	Gtk::Allocation allocation = get_allocation();
	// add board image //
	drawBoard(cr);
	// add vignettes
	drawVingnette(cr);
	// draw lines using mouse//
	drawRoute(cr);
	// draw nodes (houses) with active state
	draw_intersection_map(cr);
	// add elements scarabines //
	drawHouse(cr);


	// draw possible house constructions
	if (add_route_pressed)
	{
		drawPossibleRoutes(cr);
	}
	// draw possible route constructions
	if (add_house_pressed)
	{
			drawPossibleHouses(cr);
	}



	return true;
}

//---------------------------------- Mouse button press handling ----------------------------------//
/**
 * @brief set a permanent event box with the same dimension as the board box
 * and then every event is controlled by a condition inside this function
 * @param event  the event  (a pointer to an event  with atributes x and y event->x , event->y)
 * @return true
 * @return false
 */
bool Dessin::on_button_press_event(GdkEventButton *event)
{
	// save selected pressed
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		set_rendred_cord(event->x, event->y);
		ReafficheDessin();
	}

	if (add_route_pressed)
	{
		updateRoute(event);
	}

	if (add_house_pressed)
	{
		updateHouse(event);
	}
	return true;
}

//---------------------------------------events-------------------------------------------------------//

void Dessin::updateRoute(GdkEventButton *event)
{
	my_window f2;
	// Check if the event is a left(1) button click.
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		int selectedRoute_id = route_map.render_route(cord_x, cord_y);
		cout << "selected route " << selectedRoute_id << endl;
		if (route_map.check_possible_route(selectedRoute_id, active_player->get_player_STATE_id())) //  if route construction is possible
		{
			route_map.update_route_state(selectedRoute_id, active_player->get_player_STATE_id());
			set_add_route_pressed(false);
			ReafficheDessin();
		}
		else
		{
			// alerte widjet
			Gtk::MessageDialog d(f2, "Route construction not possible", true, Gtk::MESSAGE_ERROR);
			d.set_secondary_text("Can not Choose this position , please check the rules ");
			// Gtk::MessageDialog()
			d.run();
			set_add_route_pressed(false);
			ReafficheDessin();
		}
	}
}

void Dessin::updateHouse(GdkEventButton *event)
{
	my_window f1;

	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		int selectedHouse_id = route_map.render_node(cord_x, cord_y, 10);
		cout << "selected house " << selectedHouse_id << endl;
		// cout << route_map.check_house_construction_possible(selectedHouse_id,States::p1) << endl;
		cout << "selected house " << selectedHouse_id << endl;
		if (route_map.check_house_construction_possible(selectedHouse_id, active_player->get_player_STATE_id()))
		{
			route_map.update_intersection_state(selectedHouse_id, active_player->get_player_STATE_id());
			set_add_house_pressed(false);
			ReafficheDessin();
		}
		else
		{
			Gtk::MessageDialog d(f1, "House construction not possible", true, Gtk::MESSAGE_ERROR);
			d.set_secondary_text("Can not Choose this position , please check the rules ");
			set_add_house_pressed(false);
			// Gtk::MessageDialog()
			d.run();
			ReafficheDessin();
		}
	}
}

//-----------------------------draw Functions-----------------------------------------//

void Dessin::drawBoard(const Cairo::RefPtr<Cairo::Context> &cr)
{
	Gdk::Cairo::set_source_pixbuf(cr, pic_board, board_x, board_y); //(width, hight)
	cr->save();
	cr->rectangle(0, 0, board_width, board_height); // on ne peut pas suprimer
	cr->fill();
	cr->restore();
}

void Dessin::drawHouse(const Cairo::RefPtr<Cairo::Context> &cr)
{
	for (int i = 0; i < X.size(); i++)
	{
		cr->save();
		Gdk::Cairo::set_source_pixbuf(cr, pic2, X[i] - 50, Y[i] - 50);
		cr->rectangle(0, 0, board_width, board_height);
		cr->fill();
		cr->restore();
	}
}

void Dessin::drawVingnette(const Cairo::RefPtr<Cairo::Context> &cr)
{
	string vingnette_path, thief_vignette_path;
	string tuile_de_num;
	// T_map tuile_map = board.tuile_map;
	for (int i = 2; i < tuile_map.size; i++)
	{
		tuile_de_num = to_string(tuile_map.get_tuile_de_num(i));
		vingnette_path = "data/vigniettes/" + tuile_de_num + ".png";
		vigniette = Gdk::Pixbuf::create_from_file(vingnette_path);
		vigniette = vigniette->scale_simple((vigniette->get_height()) * 0.4, (vigniette->get_width()) * 0.4, Gdk::INTERP_BILINEAR);
		cr->save();
		Gdk::Cairo::set_source_pixbuf(cr, vigniette, tuile_map.get_tuile_x(i) - 20, tuile_map.get_tuile_y(i) - 20);
		cr->rectangle(0, 0, board_width, board_height);
		cr->fill();
		cr->restore();
	}

	thief_vignette_path = "data/vigniettes/7.png";
	vigniette = Gdk::Pixbuf::create_from_file(thief_vignette_path);
	vigniette = vigniette->scale_simple((vigniette->get_height()) * 0.4, (vigniette->get_width()) * 0.4, Gdk::INTERP_BILINEAR);
	tuile thief = tuile_map.get_thief();
	cr->save();
	Gdk::Cairo::set_source_pixbuf(cr, vigniette, thief.get_x() - 20, thief.get_y() - 20);
	cr->rectangle(0, 0, board_width, board_height);
	cr->fill();
	cr->restore();
}

void Dessin::drawPossibleRoutes(const Cairo::RefPtr<Cairo::Context> &cr)

{
	vector<route> all_routes = route_map.get_all_possible_routes(active_player->get_player_STATE_id());
	int X1, Y1, X2, Y2;
	for (int i = 0; i < all_routes.size(); i++)
	{
		X1 = all_routes[i].get_pos1().get_x();
		Y1 = all_routes[i].get_pos1().get_y();
		X2 = all_routes[i].get_pos2().get_x();
		Y2 = all_routes[i].get_pos2().get_y();

		cr->set_line_width(5);
		cr->set_source_rgba(0.18, 0.16, 0.23, 0.5);
		// cr->set_source_rgba(1, 0.2, 0.2, 0.6);
		cr->move_to(X1, Y1);
		cr->line_to(X2, Y2);
		cr->stroke();
	}
}


void Dessin::drawPossibleHouses(const Cairo::RefPtr<Cairo::Context> &cr)

{
	vector<node> all_possible_house = route_map.get_all_possible_houses(active_player->get_player_STATE_id());
	int X, Y;
	my_window f;
	string path_to_gray_arrow;

	if (all_possible_house.size() == 0 ) // no house construction is possible
	{
		Gtk::MessageDialog d(f, " No possible construction found ", true, Gtk::MESSAGE_ERROR);
			d.set_secondary_text(" Please check the rules ");
			set_add_house_pressed(false);
			// Gtk::MessageDialog()
			d.run();
			ReafficheDessin();
	}

	for (int i = 0; i < all_possible_house.size(); i++)
	{
		X = all_possible_house[i].get_x();
		Y = all_possible_house[i].get_y();
		cr->save();

		path_to_gray_arrow = "data/arrow.jpg";
		construction = Gdk::Pixbuf::create_from_file(path_to_gray_arrow);
		construction = construction->scale_simple((construction->get_height()) * 0.10, (construction->get_width()) * 0.10, Gdk::INTERP_BILINEAR);
		Gdk::Cairo::set_source_pixbuf(cr,construction, X - 10, Y - 15);

		cr->rectangle(0, 0, board_width, board_height);
		cr->fill();
		cr->restore();
	
	}
}







void Dessin::draw_intersection_map(const Cairo::RefPtr<Cairo::Context> &cr)
{
	vector<node> all_nodes = route_map.get_all_nodes();
	int X, Y; // cordonates
	States construction_state;
	string construction_path;

	for (int i = 0; i < all_nodes.size(); i++)
	{
		if (all_nodes[i].get_state() != States::empty)
		{ ////********** must change later with player

			X = all_nodes[i].get_x();
			Y = all_nodes[i].get_y();
			cr->save();

			string player_foalder=to_string (static_cast<int> (all_nodes[i].get_state()) );
			// cout <<  player_foalder <<endl;
			// snprintf(construction_path, "data/players/%d/Maison.png", player_foalder );
			construction_path = "data/players/"+player_foalder+"/Maison.png";
			construction = Gdk::Pixbuf::create_from_file(construction_path);
			construction = construction->scale_simple((construction->get_height()) * 0.4, (construction->get_width()) * 0.4, Gdk::INTERP_BILINEAR);
			Gdk::Cairo::set_source_pixbuf(cr,construction, X - 15, Y - 15);

			cr->rectangle(0, 0, board_width, board_height);
			cr->fill();
			cr->restore();
		}
	}
}

void Dessin::drawRoute(const Cairo::RefPtr<Cairo::Context> &cr)
{
	// we need to  do a for loop for all player after
	vector<route> all_routes_occupied = route_map.get_all_occupied_routes();

	for (int i = 0; i < all_routes_occupied.size(); i++)
	{
		int pos1_x = all_routes_occupied[i].get_pos1().get_x();
		int pos1_y = all_routes_occupied[i].get_pos1().get_y();
		int pos2_x = all_routes_occupied[i].get_pos2().get_x();
		int pos2_y = all_routes_occupied[i].get_pos2().get_y();
		States route_state = all_routes_occupied[i].get_route_state();
		// don't put save here
		cr->set_line_width(6);

		switch (route_state)
		{
		case States::p1:
			cr->set_source_rgb(0, 0, 100);

			break;
		case States::p2:
			cr->set_source_rgb(100, 0, 0);

			break;
		case States::p3:
			cr->set_source_rgb(0, 100, 0);

			break;
		}
		cr->move_to(pos1_x, pos1_y);
		cr->line_to(pos2_x, pos2_y);
		cr->stroke();
	}
}

//---------------------------------- Reaffiche----------------------------------//

void Dessin::ReafficheDessin()
{
	auto win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, board_width, board_height); // je touche un mon dessin et donc ça permet de redessiner
		win->invalidate_rect(r, false);
		// win->invalidate(false);
	}
}

void Dessin::setActivePlayer(Player *current_player)
{
	this->active_player = current_player;
}

void Dessin::affiche_rendred_cord()
{
	cout << cord_x << " , " << cord_y << endl;
}
