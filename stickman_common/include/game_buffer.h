#ifndef GAME_BUFFER_H
#define GAME_BUFFER_H

namespace stickman_common
{
	class game_buffer
	{
	public:
		void * memory;
		int width;
		int height;
		int stride;
	};
}

#endif // GAME_BUFFER_H

