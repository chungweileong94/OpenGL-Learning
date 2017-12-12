#ifndef MODEL_H
#define MODEL_H

namespace model {
	class Teapot
	{
	public:
		void draw();
	};

	class Box {
	public:
		void draw();
	};

	class World
	{
	public:
		Teapot teapot;
		Box box;
		void draw();
	};
}

#endif // !MODEL_H

