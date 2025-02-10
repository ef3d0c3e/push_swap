#ifndef OPTI_H
# define OPTI_H

#include "../stack/stack.h"

typedef struct s_state	t_state;

/**
 * @brief Represents an execution frame
 */
typedef struct s_frame
{
	struct s_stack sa;
	struct s_stack sb;
}	t_frame;

void opti(const t_state *s);

#endif // OPTI_H

