#include "display-menu.h"

LCDMenu::LCDMenu(uint8_t H, Callback<void(uint8_t *, bool)> draw, Callback<void()> clear)
{
    this->length = 0;
    this->head = NULL;
    this->max_len = 0;
    this->i = 0;
    this->j = 0;
    this->H = H;
    this->draw = draw;
    this->clear = clear;
}

LCDMenu::LCDMenu(uint8_t H, Callback<void(uint8_t *, bool)> draw, Callback<void()> clear, uint8_t max_len) : LCDMenu(H, draw, clear)
{
    this->max_len = max_len;
}
LCDMenu::~LCDMenu()
{
    Node *head = this->head;
    while (head)
    {
        head = head->next;
        delete head;
    }
}

void LCDMenu::add(uint8_t *name, uint8_t *addr)
{
    Node *node = new Node();
    memcpy(node->nt_name, name, 20);
    memcpy(node->addr, addr, 5);
    Node *nx = this->head;
    if (nx == NULL)
    {
        this->head = node;
        this->length++;
        return;
    }
    while (nx->next != NULL)
        nx = nx->next;
    nx->next = node;
    this->length++;
}

void LCDMenu::up()
{
    if ((this->i + this->j) > 0)
    {
        if (this->j == 0 && this->i > 0)
            this->i--;
        if (this->j > 0)
            this->j--;
        this->render();
    }
}
void LCDMenu::down()
{
    if ((this->i + this->j) < this->length - 1)
    {
        if (this->j == (this->H - 1) && (this->i + this->j) < (this->length - 1))
            this->i++;
        if (this->j < (this->H - 1))
            this->j++;
        this->render();
    }
}

uint8_t LCDMenu::getSelectedId()
{
    return (this->i + this->j);
}

Node *LCDMenu::getSelected()
{
    Node *head = this->head;
    uint8_t cur = 0;
    while (head)
    {
        if (cur == (this->i + this->j))
            return head;
        head = head->next;
        cur++;
    }
    return NULL;
}

void LCDMenu::render()
{
    this->clear();
    Node *head = this->head;
    uint8_t cur = 0;
    while (head)
    {
        if (cur >= (this->i) && cur < (this->i + this->H))
            this->draw(head->nt_name, cur == this->i + this->j);
        /*if (cur > this->H)
            return;*/
        head = head->next;
        cur++;
    }
}