#include "backtrack.h"
#include "../state/state.h"

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
	if (s->sa.size != ss->sa.size || s->sb.size != ss->sb.size)
		return (0);
	return (memeq(s->sa.data, ss->sa.data, s->sa.size * sizeof(int))
		&& memeq(s->sb.data, ss->sb.data, s->sb.size * sizeof(int)));
}

size_t bt_find_future(const t_backtrack *bt, const size_t start, const t_state* state)
{
	const t_savestate	*future;
	size_t				i;
	size_t				best;

	i = 1;
	best = 0;
	while (i < bt->cfg.max_frame_lookhead && start + i + 1 < bt->saves_size)
	{
		future = bt->saves + start + i;
		if (bt_compare_states(state, future))
			best = i;
		++i;
	}
	return (best);
}
