
#ifndef  THREAD_H
#define  THREAD_H

	UINT   StartSocketThread( LPVOID lParam );
	//  пч╦деДжцнд╪Ч
	UINT   ModifyConfigThread( LPVOID lParam );
	UINT   ConfigSocketThread( LPVOID lParam );
	UINT   ModifyFileConfigThread( LPVOID lParam );
#endif //THREAD_H