#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

/**
 * @brief The stack data structure
 *
 * TODO: Use a deque with capacity = 3 * (N=original capacity), with data at the center
 * When the top/bottom is reached, use memcpy instead of memmove to recenter the stack, this guarantees
 * that the expensive copying (of N elements) only happens every N rotation operations, therefore guaranteeing a O(1) time complexity
 */
struct s_stack
{
	int		*data;
	size_t	size;
	/* const */ size_t	capacity;
	/*
	const int* start;
	const int* end;
	*/
	
};

/**
 * @brief All defined stack operations
 *
 * These are operation to be performed by the @ref stack_op function
 *
 * # Encoding
 *
 * Here is the operations encoding scheme:
 *  * Lower 2 bits: Stack selector, 0b01 for A, 0b10 for B, 0b11 for A and B
 *  * Next 3 bits: Operator selector:
 *  *- 0b001: Swap
 *  *- 0b010: Push
 *  *- 0b011: Rotate
 *  *- 0b100: Reverse Rotate
 *
 *  Note: Push with stack selector `0b11` is invalid.
 *
 * # Implementation
 *
 * All operations are trivially O(1), except for rotations. By using a deque as
 * the stack, we can amortize the expensive `memcopy` that would happens around
 * every N rotate operations. Therefore rotations are amortized O(1).
 */
enum e_stack_op
{
	__STACK_OP_SEL_A = 0b00001,
	__STACK_OP_SEL_B = 0b00010,
	__STACK_OPERAND	= 0b00011,
	__STACK_OP_SWAP = 0b00100,
	__STACK_OP_PUSH = 0b01000,
	__STACK_OP_ROTATE = 0b01100,
	__STACK_OP_REV_ROTATE = 0b10000,
	__STACK_OPERATOR = 0b11100,
	/**
	 * @brief Swaps A's top 2 elements
	 */
	STACK_OP_SA = __STACK_OP_SWAP | __STACK_OP_SEL_A,
	/**
	 * @brief Swaps B's top 2 elements
	 */
	STACK_OP_SB = __STACK_OP_SWAP | __STACK_OP_SEL_B,
	/**
	 * @brief Performs SA and SB
	 */
	STACK_OP_SS = __STACK_OP_SWAP | __STACK_OP_SEL_A | __STACK_OP_SEL_B,
	/**
	 * @brief Moves B's top to A's top
	 */
	STACK_OP_PA = __STACK_OP_PUSH | __STACK_OP_SEL_A,
	/**
	 * @brief Moves A's top to B's top
	 */
	STACK_OP_PB = __STACK_OP_PUSH | __STACK_OP_SEL_B,
	/**
	 * @brief Rotates A topwise
	 */
	STACK_OP_RA = __STACK_OP_ROTATE | __STACK_OP_SEL_A,
	/**
	 * @brief Rotates B topwise
	 */
	STACK_OP_RB = __STACK_OP_ROTATE | __STACK_OP_SEL_B,
	/**
	 * @brief Performs RA and RB
	 */
	STACK_OP_RR = __STACK_OP_ROTATE | __STACK_OP_SEL_A | __STACK_OP_SEL_B,
	/**
	 * @brief Rotates A bottomwise
	 */
	STACK_OP_RRA = __STACK_OP_REV_ROTATE | __STACK_OP_SEL_A,
	/**
	 * @brief Rotates B bottomwise
	 */
	STACK_OP_RRB = __STACK_OP_REV_ROTATE | __STACK_OP_SEL_B,
	/**
	 * @brief Performs RRA and RRB
	 */
	STACK_OP_RRR = __STACK_OP_REV_ROTATE | __STACK_OP_SEL_A | __STACK_OP_SEL_B,
};

/**
 * @brief Creates a new @ref s_stack with given capacity
 *
 * @param capacity The stack's capacity
 *
 * @returns The newly created stack, exit(1) on malloc failure. The stack will
 * have to be deallocated with @ref stack_free
 */
struct s_stack	stack_new(size_t capacity);
/**
 * @brief Deallocates a @ref s_stack
 *
 * @param s Stack to free
 */
void			stack_free(struct s_stack *s);
/**
 * @brief Utility to get the name of a stack operation
 *
 * @param op The @ref stack_op to get the name of
 *
 * @returns The name of `op`
 */
const char		*stack_op_name(enum e_stack_op op);
/**
 * @brief Applies a @ref stack_op over stack A's and B's
 *
 * See @ref stack_op for more informations about operations.
 * The sorting algorithm should call @ref op from push_swap.h so that it logs
 * out the operations to stdout.
 *
 * @param sa Stack A
 * @param sb Stack B
 * @param op Operation to apply
 */
void			stack_op(struct s_stack *sa,
					struct s_stack *sb,
					enum e_stack_op op);

#endif // STACK_H
