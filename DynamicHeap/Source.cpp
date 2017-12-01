#include <iostream>
#include "DynamicHeap.h"

int main()
{
	try {
		DynamicHeap<int> heap1;		//						   ROOT*
									//							|
		heap1.push(10);				//					 _______14______			Level 0
		heap1.push(3);				//					|				|
		heap1.push(7);				//				___12___		____10___		Level 1
		heap1.push(1);				//				|		|		|		 |
		heap1.push(3);				//			  __11	    3		7		 1		Level 2
		heap1.push(14);				//			 |		 	  
		heap1.push(20);				//			 3		 							Level 3
		heap1.push(12);
		heap1.pop();
		heap1.push(11);
		heap1.print();

		heap1.toMinHeap();
		heap1.print();

		DynamicHeap<int> heap2;
		heap2.push(32);
		heap2.push(4);
		heap2.push(45);
		heap2.push(-2);
		heap2.push(8);

		heap2.join(heap1);
		heap2.print();

		system("pause");
		return 0;
	}
	catch (Exception& err)
	{
		std::cout << err;
	}
	catch (...)
	{
		std::cout << "Exception." << std::endl;
	}
}