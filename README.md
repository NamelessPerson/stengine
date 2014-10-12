Josh Phillips Coding Standard
==================================================================================================
v1.0
__________________________________________________________________________________________________

Naming
--------------------------------------------------------------------------------------------------

Variables and Function are mixed case starting with a lowercase.
		
		thisIsAVeryLongVariableName;
		thisIsAVeryLongFunctionName();

Classes are mixed case starting with a capital.
		
		ThisIsAVeryLongClassName obj;

Get and set methods should match the name of their variable.
		
		int x;
		int getX();
		void setX();

Private class variables that are seen from the outside but not changed should be started with an _ and their function should not include "get"

		int _length;
		int length();

Constants should be in all uppercase with _ separating words

		THIS_IS_A_REALLY_LONG_CONSTANT_NAME = 0;

General
--------------------------------------------------------------------------------------------------

Braces trail the end of function, class, and control block declarations.
Closing Brackets are on their own line. If they are not being followed by another closing brace they should be followed by a new line.

		void foo(int x){
			if(something){
				if(somethingElse){
					if(yetAnotherSomething){
						function();
					}
				}

				else{
					function();
				}
			} 

			else{
				function();
			}
		}

Groups of more than 4 variable or function declarations should be separated with a new line.
Groups of <4 may also be separated to increase readdability.

		int x;
		int y;

		bool a;
		bool b;
		bool c;
		bool d;

		double one;

Varaibles should only be declared on the same line if incremental or commony grouped.

		int x,y,z;
		double length, width, height.

Always

		int* ptr;

Over

		int *ptr;
		int * ptr;

Never declare pointers and variables on same line;

		int* ptr1, ptr2;
		int x, y;

Error checking, newline, variable declaration, new line, meethod body.

In classes: Always declare constants first, variables second, and functions last.

		Class A{
		public:
			const int PI = 3.14;

			int x,y,z;
			int a,b,c;

			A();
			foo();
			foo2();
		private:
			int i,j,k;

			fooBar();
		}

Comments
--------------------------------------------------------------------------------------------------

Single and in-line comments with //.

Multi-line comments with /* */

Documentation with

		/*
		====================================================
			Function/Class name

		Description
		====================================================
		*/