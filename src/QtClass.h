#pragma once

#include <Character>

class QtClass  : public Character
{
	Q_OBJECT

public:
	QtClass(QObject *parent);
	~QtClass();
};
