#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

enum KEYS{LEFT,RIGHT,SPACE}; //nazywaM keysy bo bedzie ciezko zapamietac z tablicy co jest czym

int main(void)
{
																		//INICJACJE MODU£ÓW


	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//DEKLAROWANIE ZMIENNYCH C


	int szerokosc = 1920;
	int wysokosc = 1080;

	int klatkowe_start = 0;


	int kamera_x = 0;

	int czas_po_utracie_zycia = 120;

	int grawitacja = 15;

	bool done = false;
	bool przerys = true;
	bool skok = false;
	bool start = false;
	bool smierc = false;

	bool sciezka_w1 = false;
	bool sciezka_w2 = false;

	int pos_x = 10;
	int pos_y = (wysokosc*3)/4;

	int kolider_w1=0;
	int kolider_w2=0;

	int ilosc_zyc = 3;

	int kolider_x = pos_x;
	int kolider_y = pos_y;

	int FPS = 60;
	int ostatni_ruch = 0;

	int grunt1_x = 0;
	int grunt1_y = pos_y + 80;



	bool keys[4] = { false,false, false};//bo ich nie trzymasz


 //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//DEKLARACJA ZMNIENNYCH ALLEGRO


	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bohater = NULL;
	ALLEGRO_BITMAP *grunt1 = NULL;
	ALLEGRO_BITMAP *wrog1 = NULL;
	ALLEGRO_BITMAP *wrog2 = NULL;
	ALLEGRO_BITMAP *tlo_gl = NULL;
	ALLEGRO_BITMAP *tlo2 = NULL;
	ALLEGRO_BITMAP *zycie = NULL;
	ALLEGRO_BITMAP *tytul = NULL;
	ALLEGRO_BITMAP *tytul1 = NULL;
	ALLEGRO_BITMAP *tytul2 = NULL;
	ALLEGRO_BITMAP *tytul3 = NULL;
	ALLEGRO_BITMAP *smierc2 = NULL;
	ALLEGRO_BITMAP *zycie_zielone = NULL;
	ALLEGRO_BITMAP *zycie_czerwone = NULL;

	ALLEGRO_FONT *font18 = al_load_ttf_font("verdana.ttf", 18, 0);


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//TESTY INICJACJI



	if (!al_init())
		return -1;

	okno = al_create_display(szerokosc, wysokosc);

	if (!okno)
		return -1;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//PRZYPISYWANIE BITMAP


	bohater = al_load_bitmap("player model.png");
	grunt1 = al_load_bitmap("grunt1.png");
	wrog1 = al_load_bitmap("wrog.png");
	wrog2 = al_load_bitmap("wrog.png");
	tlo_gl = al_load_bitmap("tlo_gl.png");
	tlo2 = al_load_bitmap("tlo2.png");
	zycie = al_load_bitmap("zycie.png");
	tytul = al_load_bitmap("tytul.png");
	tytul1 = al_load_bitmap("tytul1.png");
	tytul2 = al_load_bitmap("tytul2.png");
	tytul3 = al_load_bitmap("tytul3.png");
	zycie_zielone = al_load_bitmap("zycie_zielone.png");
	zycie_czerwone = al_load_bitmap("zycie_czerwone.png");

	smierc2 = al_load_bitmap("tytul_smierc.png");





//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//ZDARZENIA I TIMERY


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																		//G£ÓWNA PÊTLA
	while (start!=true)
	{
		ALLEGRO_EVENT start1;
		al_wait_for_event(event_queue, &start1);

		if (start1.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
		{
			switch (start1.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				start = true;
				break;
			}
		}

		klatkowe_start=klatkowe_start+2;


		if ((klatkowe_start >= 0) && (klatkowe_start < 60))
		{
			al_draw_bitmap(tytul1, 0, 0, 0);
		}
		if ((klatkowe_start >= 60) && (klatkowe_start < 120))
		{
			al_draw_bitmap(tytul2, 0, 0, 0);
		}
		if ((klatkowe_start >= 120) && (klatkowe_start < 180))
		{
			al_draw_bitmap(tytul3, 0, 0, 0);
		}

		if (klatkowe_start == 180)
		{
			klatkowe_start = 0;
		}

		al_flip_display();
	}

	while (!smierc)
	{

		while (!done)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);




			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					ostatni_ruch = 1;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					ostatni_ruch = 0;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					break;
				}
			}

			else if (ev.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					smierc = true;
					done = true;
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//X wylacza okno
			{
				done = true;
			}


			//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																				//TIMER


			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{

				if (czas_po_utracie_zycia != 0)
				{
					czas_po_utracie_zycia -= 1;
				}

				if ((pos_y - 66 > 1080) || (ilosc_zyc == -1))
				{
					done = true;
				}

				if (sciezka_w1 == false)
				{
					kolider_w1 += 1;
					if (kolider_w1 == 30)
					{
						sciezka_w1 = true;
					}
				}
				else
				{
					kolider_w1 -= 1;
					if (kolider_w1 == 0)
					{
						sciezka_w1 = false;
					}
				}


				if (sciezka_w2 == false)
				{
					kolider_w2 += 1;
					if (kolider_w2 == 60)
					{
						sciezka_w2 = true;
					}
				}
				else
				{
					kolider_w2 -= 1;
					if (kolider_w2 == 0)
					{
						sciezka_w2 = false;
					}
				}


				if (pos_x < 960)
				{
					pos_x -= keys[LEFT] * 5;
					pos_x += keys[RIGHT] * 5;
					kolider_x = pos_x;
				}

				else if (kamera_x == 0)
				{
					pos_x = 955;
					kolider_x = pos_x;
				}

				if (pos_x >= 960)
				{
					kamera_x -= keys[RIGHT] * 5;
					kamera_x += keys[LEFT] * 5;
					kolider_x += keys[RIGHT] * 5;
					kolider_x -= keys[LEFT] * 5;
				}

				if (keys[SPACE] == true)
				{
					pos_y -= grawitacja;
					grawitacja -= 1;
					skok = true;

					if (grawitacja == -16)
					{
						keys[SPACE] = false;
						grawitacja = 15;
						skok = false;
					}
				}

				if ((!(((kolider_x + 41 > 0) && (kolider_x + 41 <= 795) && (pos_y + 15 == 825))
					|| ((kolider_x + 41 > 850) && (kolider_x + 41 < 795 + 850) && (pos_y + 15 == 825))
					|| ((kolider_x + 41 > 850 + 795) && (kolider_x + 41 < 795 + 795 + 850) && (pos_y + 15 == 825))
					|| ((kolider_x + 41 > 850 + 795 + 795) && (kolider_x + 41 < 795 + 795 + 795 + 850) && (pos_y + 15 == 825))
					|| (skok == true))))
				{
					pos_y += 20;
				}

				if ((((kolider_x > grunt1_x + 1000 + kolider_w1) && (kolider_x < grunt1_x + 1000 + kolider_w1 + 220)) || ((kolider_x > grunt1_x + 1300 + kolider_w2) && (kolider_x < grunt1_x + 1300 + kolider_w2 + 220))) && (czas_po_utracie_zycia == 0))
				{
					ilosc_zyc -= 1;
					czas_po_utracie_zycia = 120;
				}




				//jak prawda to 1 razy to a jak nie to nie ma
				przerys = true;//ROBI ZA WZNOWIENIE CZASU JAK SUPER HOT
			}


			//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																				//KOLEJKOWANIE WYDARZEÑ/WYŒWIETLANIA


			if (przerys && al_is_event_queue_empty(event_queue))//unika ghostow
			{
				przerys = false;


				al_draw_bitmap(tlo_gl, 0 + kamera_x / 3, 0, 0);
				al_draw_bitmap(tlo2, (0 + kamera_x * 2) / 3, 0, 0);

				if (ilosc_zyc == 3)
				{
					al_draw_bitmap(zycie, 30 + 138, 10, 0);
				}


				if (ilosc_zyc >= 2)
				{
					al_draw_bitmap(zycie, 20 + 69, 10, 0);
				}


				if (ilosc_zyc >= 1)
				{
					al_draw_bitmap(zycie, 10, 10, 0);
				}




				//al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 255));
				if (ostatni_ruch == 0)
				{
					al_draw_bitmap(bohater, pos_x, pos_y + 15, 0);
				}
				else
				{
					al_draw_bitmap(bohater, pos_x, pos_y + 15, ALLEGRO_FLIP_HORIZONTAL);
				}

				al_draw_bitmap(grunt1, grunt1_x + kamera_x, grunt1_y, 0);
				al_draw_bitmap(grunt1, grunt1_x + 850 + kamera_x, grunt1_y, 0);
				al_draw_bitmap(grunt1, grunt1_x + 1645 + kamera_x, grunt1_y, 0);
				al_draw_bitmap(grunt1, grunt1_x + 2240 + kamera_x, grunt1_y, 0);


				al_draw_bitmap(wrog1, grunt1_x + 1000 + kamera_x + kolider_w1, grunt1_y - 80, 0);
				al_draw_bitmap(wrog2, grunt1_x + 1300 + kamera_x + kolider_w2, grunt1_y - 80, 0);

				al_draw_bitmap(zycie_zielone, grunt1_x + 1000 + kamera_x + kolider_w1 + 40, grunt1_y - 120, 0);
				al_draw_bitmap(zycie_zielone, grunt1_x + 1300 + kamera_x + kolider_w2 + 40, grunt1_y - 120, 0);
				al_draw_bitmap(zycie_zielone, grunt1_x + 1000 + kamera_x + kolider_w1 - 40, grunt1_y - 120, 0);
				al_draw_bitmap(zycie_zielone, grunt1_x + 1300 + kamera_x + kolider_w2 - 40, grunt1_y - 120, 0);

				al_draw_textf(font18, al_map_rgb(50, 0, 255), 350, 50, ALLEGRO_ALIGN_LEFT, "%i", grawitacja);
				al_draw_textf(font18, al_map_rgb(200, 0, 255), 150, 50, ALLEGRO_ALIGN_LEFT, "%i", pos_y + 15);
				al_draw_textf(font18, al_map_rgb(255, 0, 0), 1700, 50, 0, "Kolider x to: %i", kolider_x);








				//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
																					//WYŒWIETLANIE


				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}

		

		}

		
			ALLEGRO_EVENT smierc1;
			al_wait_for_event(event_queue, &smierc1);

			if (smierc1.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
			{
				switch (smierc1.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					smierc = true;
					break;
				case ALLEGRO_KEY_SPACE:
					done = false;
					pos_x = 10;
					pos_y = (wysokosc * 3) / 4;
					kamera_x = 0;
					break;
				}
			}


				al_draw_bitmap(smierc2, 0, 0, 0);
			

			

			al_flip_display();
		}
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
		//CZYSZCZENIE
		//ten github...

		al_destroy_display(okno);
		al_destroy_bitmap(bohater);
		al_destroy_bitmap(grunt1);
		al_destroy_bitmap(wrog1);
		al_destroy_bitmap(wrog2);
		al_destroy_bitmap(tlo2);
		al_destroy_bitmap(tlo_gl);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);





	return 0;
}