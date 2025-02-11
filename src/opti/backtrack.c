#include "backtrack.h"
#include "../state.h"

static inline int	memeq(const void *l, const void *r, size_t N)
{
	const unsigned char	*end = (unsigned char*)r + N;
	const unsigned char	*wl;
	const unsigned char	*wr;

	wl = l;
	wr = r;
	while (end - wr >= (long int)sizeof(unsigned long int))
	{
		if (*(unsigned long int *)wl != *(const unsigned long int *)wr)
			return (0);
		wl += sizeof(unsigned long int);
		wr += sizeof(unsigned long int);
	}
	while (wr != end)
	{
		if (*wl != *wr)
			return (0);

		++wl;
		++wr;
	}
	return (1);
}

int	bt_compare_states(const t_state *s, const t_savestate *ss)
{
	size_t	i;
	
	if (s->sa.size != ss->sa.size || s->sb.size != ss->sb.size)
		return (0);
	i = 0;
	return (memeq(s->sa.data, ss->sa.data, s->sa.size)
		&& memeq(s->sb.data, ss->sb.data, s->sb.size)
			);
}
