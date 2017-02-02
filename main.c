#include <stdio.h>
#include <stdlib.h>

typedef struct  __attribute__ ((packed)) node{
    char digit;
    struct node * next;
} Node;

enum SIGN { POSITIVE, NEGATIVE };

typedef struct __attribute__((packed)) {
	enum SIGN sign;
	Node * head;
} BigInt;

int BigInt_isNAN(BigInt bInt)
{
	return (bInt.head == NULL);
}

static Node * Create(char digit)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node -> digit = digit, node -> next = NULL;
    return node;
}

BigInt BigInt_Gets(char * string)
{
    if(string == NULL)
        return (BigInt) {POSITIVE, NULL};
    Node * head = NULL, * node = NULL;
	enum SIGN FLAG = POSITIVE;
    int i = 0;
	if (string[i] == '-') FLAG = NEGATIVE, i++;
    while(string[i] ^ '\0' && string[i] >= '0' && string[i++] <= '9');
    while(string[--i] == '0');
    while(i >= 0){
        if(!node)
            head = node = Create(string[i]);
        else
            node -> next = Create(string[i]), node = node -> next;
        --i;
    }
    if(head == NULL)
        head = Create('0');
	return (BigInt) { FLAG, head };
}

int Print(Node * node)
{
	if (node == NULL)
		return 0;
	int d = Print(node->next);
	putchar(node->digit);
	return 1 + d;
}

int BigInt_Puts(BigInt bInt)
{
    if(BigInt_isNAN(bInt))
        return 0;
	if(bInt.sign == NEGATIVE)
		putchar('-');
	return Print(bInt.head);
}

static int Free(Node * node)
{
	if (node == NULL)
		return 0;
	Free(node->next);
	free(node);
	return 1;
}

int BigInt_Free(BigInt bInt)
{
	if (BigInt_isNAN(bInt))
		return 0;
	Free(bInt.head);
	return 1;
}

static Node * Cpy(Node * bNum)
{
	Node * head = NULL, * node = NULL;
	while (bNum != NULL) {
		if (!node)
			head = node = Create(bNum->digit);
		else
			node->next = Create(bNum->digit), node = node->next;
		bNum = bNum->next;
	}
	return head;
}

BigInt BigInt_Cpy(BigInt bInt)
{
	if (BigInt_isNAN(bInt))
		return (BigInt) {POSITIVE, NULL};
	return (BigInt) { bInt.sign, Cpy(bInt.head) };
}

BigInt BigInt_Abs(BigInt bInt)
{
	BigInt bAbs = BigInt_Cpy(bInt);
	return (BigInt) { POSITIVE, bAbs.head };
}

int BigInt_isNonZero(BigInt bInt)
{
	return !(BigInt_isNAN(bInt) || (bInt.head -> digit == 0 && bInt.head -> next == NULL));
}

static Node * Add(Node * bInt_a, Node * bInt_b)
{
    if(bInt_a == NULL)
        return Cpy(bInt_b);
    if(bInt_b == NULL)
        return Cpy(bInt_a);
    Node * head = NULL, * node = NULL;
    int carry = 0, sum = 0;
    while(bInt_a && bInt_b){
        sum = bInt_a -> digit + bInt_b -> digit + carry - 2 * '0';
        carry = sum / 10, sum = sum % 10 + '0';
        if(!node)
            head = node = Create(sum);
        else
            node -> next = Create(sum), node = node -> next;
        bInt_a = bInt_a -> next, bInt_b = bInt_b -> next;
    }
    while(carry){
        if(bInt_a)
            sum = bInt_a -> digit + carry - '0', bInt_a = bInt_a -> next;
        if(bInt_b)
            sum = bInt_b -> digit + carry - '0', bInt_b = bInt_b -> next;
        else
            sum = carry;
        carry = sum / 10, sum = sum % 10 + '0';
        node -> next = Create(sum), node = node -> next;
    }
    if(bInt_a)
        node -> next = Cpy(bInt_a);
    if(bInt_b)
        node -> next = Cpy(bInt_b);
    return head;
}

BigInt BigInt_Add(BigInt bInt_a, BigInt bInt_b)
{
	if (BigInt_isNAN(bInt_a))
		return BigInt_Cpy(bInt_b);
	if (BigInt_isNAN(bInt_b))
		return BigInt_Cpy(bInt_a);
	if (bInt_a.sign == bInt_b.sign)
		return (BigInt) { bInt_a.sign, Add(bInt_a.head, bInt_b.head) };
}

int main(void) {
	char string[255];
	scanf("%s", string);
	BigInt bInt_1 = BigInt_Gets(string);
	//BigInt bInt_cpy = BigInt_Cpy(bInt);
	scanf("%s", string);
	BigInt bInt_2 = BigInt_Gets(string);
	BigInt bInt_3 = BigInt_Add(bInt_1, bInt_2);
	//BigInt_Puts(bInt_1);
	BigInt_Free(bInt_1);
	BigInt_Free(bInt_2);
	//BigInt_Puts(bInt_cpy);
	//BigInt_Free(bInt_cpy);
	BigInt_Puts(bInt_3);
	BigInt_Free(bInt_3);
	return 0;
}