# GUI  
---  

## Employee  
- 生成时在柜台处  
> 柜台还没画上可先用宏定义坐标  

## Consumer  
- 进店排队，具体排队方向怎么方便怎么来  
	- 槽函数：void enQueue(Consumer* consumer)  

- 买完咖啡，当前顾客进入等待区，其它顾客依次向前一个位置挪动  
	- 槽函数：void waitCat(Consumer* consumer), void moveForward(QQueue<Consumer*> *wConsumer)  
> Root里有一个排队顾客队列，声明为QQueue<Consumer*> *wConsumer，用的是Qt里的队列  

- 撸猫  
	- 槽函数：void cating(Consumer* consumer, Cat* cat)  
> 同时把要撸猫的顾客和被撸的猫传进来  
> 这里可能需要跟猫的gui有传参之类的交互，你俩商量吧  

## Cat  
- 被撸就到撸猫区，被撸完就回等待被撸区  
	- 槽函数：void work(Cat* cat), void home(Cat* cat)
> work()里应该有和consumer统一坐标的地方，你俩商量  
