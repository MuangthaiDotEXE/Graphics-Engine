#pragma once

#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

namespace Engine
{
	class Object 
	{
	public:
		Object();
		virtual ~Object() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
