# Canvas

+ protected
  + id
  + _color

+ public
  + virtual int getID();
  + virtual void setColor();
  + virtual QColor color();

## Circle



## Line



# Container

+ private
  + QVector<Circle> _circle
  + QVector<Line>  _line
  + ColorList mld

+ public
  + Circle circle(int i)
  + Line line(int i)
  + bool isInCircle(QPoint x, int range = 0)
  + int getCircleIndex(QPoint x)
  + int insertCircle(QPoint pos, int size = defaultSize)
  + QPair<int,int> insertLine(QPoint beg, QPoint end)