extern void tray_callback(int itemId);

void init_tray(const char* title);
void set_tray_menu_item(int id, const char* title, int disabled);
void set_tray_icon(int);
void native_loop();
void exit_loop();