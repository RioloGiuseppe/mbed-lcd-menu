#include "mbed.h"

class Node
{
  public:
    Node *next;
    uint8_t nt_name[14];
    uint8_t addr[5];
};

class LCDMenu
{
  private:
    uint8_t max_len;
    Node *head;
    uint8_t i, j, H;
    Callback<void(uint8_t*,bool)> draw;
    Callback<void()> clear;

  public:
    uint8_t length;
    LCDMenu(uint8_t, Callback<void(uint8_t*,bool)>, Callback<void()>);
    LCDMenu(uint8_t, Callback<void(uint8_t*,bool)>, Callback<void()>, uint8_t);
    ~LCDMenu();
    void add(uint8_t *, uint8_t *);
    void up();
    void down();
    Node *getSelected();
    uint8_t getSelectedId();
    void render();
};