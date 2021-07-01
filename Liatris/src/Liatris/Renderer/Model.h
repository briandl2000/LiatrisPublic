#pragma once

namespace Liatris
{
	class Model
	{
	public:
		virtual ~Model() = default;

		virtual void Render() = 0;
		
		static Ref<Model> Create(std::string path);


	
	private:
	};
	
}
