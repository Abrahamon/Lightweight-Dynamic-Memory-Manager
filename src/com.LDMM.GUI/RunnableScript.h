/*
 * RunnableScript.h
 *
 *  Created on: Apr 5, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_GUI_RUNNABLESCRIPT_H_
#define SRC_COM_LDMM_GUI_RUNNABLESCRIPT_H_
#include <pthread.h>

class RunnableScript {
public:
	RunnableScript();
	virtual ~RunnableScript();

	void* run(void){
		system("python /home/fabian/workspace2/C++/LDMM/Lightweight-Dynamic-Memory-Manager/src/MemMonitor.py");
		while(true){
		}
	}
	static void* runScript(void* context){
		return ((RunnableScript*)context)->run();
	}

	void st(){
		pthread_t hilo;
		pthread_create(&hilo,0,&RunnableScript::runScript,(void *)this);
		pthread_detach(hilo);
	}
};

#endif /* SRC_COM_LDMM_GUI_RUNNABLESCRIPT_H_ */
