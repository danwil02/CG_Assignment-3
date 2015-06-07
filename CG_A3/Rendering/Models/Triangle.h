#include "Model.h"

#define VALS_PER_VERT 3
#define VALS_PER_COLOUR 4

namespace Rendering
{
	namespace Models
	{
		class Triangle : public Model
		{
		public:
			Triangle();
			~Triangle();

			void Create();
			virtual void Update(unsigned int flags) override final;
			virtual void Draw() override final;
		};
	}
}