#ifndef LAYOUT_H
#define LAYOUT_H

#define GRID_BOX_WIDTH                  22
#define GRID_BOX_HEIGHT                 26
#define ANSWER_BTN_WIDTH                70
#define ANSWER_BTN_HEIGHT               26

#include <QLayout>

using namespace std;

/* Create all GUI layout
*/
QHBoxLayout * createLayout();

/* Update grid
** Set labels values into given grid (gridLayout)
** gridLayout:  grid layout where labels are setted
*/
void updateGrid(QGridLayout * girdLayout);

#endif // LAYOUT_H
