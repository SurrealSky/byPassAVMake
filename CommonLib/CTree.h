#ifndef _AVL_H_
#define _AVL_H_
#include <iostream>
#define LH	1		//左高
#define EH	0		//等高
#define RH	-1		//右高
//平衡二叉排序树结点结构 
template <class ElemType,class KeyType>
struct AVLNode{
    ElemType data;					        //结点数据域
    AVLNode<ElemType,KeyType> *lchild;		//结点左孩子
    AVLNode<ElemType,KeyType> *rchild;		//结点右孩子
	int bf;							        //结点平衡因子
};
//平衡二叉排序树类
template< class ElemType,class KeyType>
class AVL{
public:
	AVL ();				
	~AVL ( );
	AVLNode<ElemType,KeyType> *Root() const{return m_T;};//返回平衡二叉树的根指针
	AVLNode<ElemType,KeyType> *FindMin(AVLNode<ElemType,KeyType> *node) const;
	AVLNode<ElemType,KeyType> *FindMax(AVLNode<ElemType,KeyType> *node) const;
	bool Insert(const ElemType & e,const KeyType & key);//平衡二叉排序树中插入关键字为key的元素e
	bool Delete(const KeyType & key);//平衡二叉排序树中删除关键字为key的元素
	AVLNode<ElemType,KeyType>* Search(const KeyType & key);//平衡二叉排序树中查找是否存在关键字为key的元素
	int GetDepth();	//求平衡二叉排序树的深度
	void InorderTraverse();	//中序遍历平衡二叉排序树
private:
	AVLNode<ElemType,KeyType> * m_T;//平衡二叉排序树根指针
	void _Destroy(AVLNode<ElemType,KeyType> * &T);//销毁平衡二叉排序树
	void _RRotate(AVLNode<ElemType,KeyType> * &T);//右旋操作
	void _LRotate(AVLNode<ElemType,KeyType> * &T);//左旋操作
	void _LeftBalance(AVLNode<ElemType,KeyType> * &T);//左平衡处理
	void _RightBalance(AVLNode<ElemType,KeyType> * &T);	//右平衡处理
	bool _Insert(AVLNode<ElemType,KeyType> * &T,ElemType e,KeyType key,bool &bTaller);//平衡二叉排序树中插入关键字为key的元素，并保持平衡状态
	bool _Delete(AVLNode<ElemType,KeyType> * &T,KeyType key,bool &bShorter);//平衡二叉排序树中删除关键字为Key的元素，并保持平衡状态
	AVLNode<ElemType,KeyType>* _Search(AVLNode<ElemType,KeyType>* T,KeyType key);//平衡二叉排序树中查找是否存在关键字key
	int  _GetDepth(AVLNode<ElemType,KeyType>* T);//求平衡二叉排序树的深度
	void _InorderTraverse(AVLNode<ElemType,KeyType>* T);//中序遍历二叉树
};
template< class ElemType,class KeyType>
AVL<ElemType,KeyType>::AVL ()
{
	m_T = NULL;
}
template< class ElemType,class KeyType>
AVL<ElemType,KeyType>::~AVL ( )
{
	_Destroy(m_T);
}

template< class ElemType,class KeyType>
 AVLNode<ElemType,KeyType>* AVL<ElemType,KeyType>::FindMin(AVLNode<ElemType,KeyType> *node) const
 {
	 if (node == NULL)
          return NULL;
	 if (node->lchild == NULL)
          return node;
	 return FindMin(node->lchild);
 }

 template< class ElemType,class KeyType>
 AVLNode<ElemType,KeyType>* AVL<ElemType,KeyType>::FindMax(AVLNode<ElemType,KeyType> *node) const
 {
	 if (node == NULL)
          return NULL;
	 if (node->rchild == NULL)
          return node;
	 return FindMax(node->rchild);
 }

template< class ElemType,class KeyType>
bool AVL<ElemType,KeyType>::Insert(const ElemType & e,const KeyType & key)
{
	bool bTaller;
	return _Insert(m_T, e, key,bTaller);	
}
template< class ElemType,class KeyType>
bool AVL<ElemType,KeyType>::Delete(const KeyType & key)
{
	bool bShorter;
	return _Delete(m_T, key, bShorter);	
}
//在平衡二叉排序树中查找关键字为key的元素是否存在
template< class ElemType,class KeyType>
AVLNode<ElemType,KeyType>* AVL<ElemType,KeyType>::Search(const KeyType & key)
{
	return _Search(m_T,key);
}
// 初始条件: 平衡二叉排序树T存在。操作结果: 返回T的深度     
template <class ElemType,class KeyType> 
int AVL<ElemType,KeyType>::GetDepth()
{
    return _GetDepth(m_T);
}
// 中序遍历二叉树        
template <class ElemType,class KeyType>
void AVL <ElemType,KeyType>::InorderTraverse()
{
    _InorderTraverse(m_T);
} 
//销毁平衡二叉排序树
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_Destroy(AVLNode<ElemType,KeyType> * &T)
{
	 if(T){
        _Destroy(T->lchild);
        _Destroy(T->rchild);
        delete T;
        }
    T=NULL;  
}
//对以T为根的二叉排序树作右旋操作，操作后T指向新的树根结点
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_RRotate(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * TempAVL;
	TempAVL = T->lchild;			//TempAVL指向T的左子树的根结点
	T->lchild = TempAVL->rchild;	//TempAVL的右子树挂接作为T的左子树
	TempAVL->rchild = T;			
	T = TempAVL;					//T指向新的树根结点
}
//对以T为根的二叉排序树作左旋操作。操作后T指向新的树根结点
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_LRotate(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * TempAVL;
	TempAVL = T->rchild;			//TempAVL指向T的右子树的根结点
	T->rchild = TempAVL->lchild;	//TempAVL的左子树挂接作为T的右子树
	TempAVL->lchild = T;
	T = TempAVL;					//T指向新的树根结点
}
//对以T为根结点的二叉排序树作左平衡处理，处理完毕后T指向新的树根结点
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_LeftBalance(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * tr, * TempAVL;
	tr = T->lchild;					//tr指向T的左子树的根结点
	switch(tr->bf){					//根据tr的平衡因子，作相应调整
	case LH:						//新结点插在T的左孩子的左子树上，作右旋操作
		T->bf = EH;
		_RRotate(T);
		tr->bf = EH;
		return;
	case RH:						//新结点插在T的左孩子的右子树上，作两次旋转操作
		TempAVL = tr->rchild;		//TempAVL指向tr的右子树的根结点上
		switch(TempAVL->bf){
		case LH:
			T->bf = RH;
			tr->bf = EH;
			break;
		case EH:
			T->bf = tr->bf = EH;
			break;
		case RH:
			T->bf = EH;
			tr->bf = LH;
			break;
		}
		TempAVL->bf = EH;
		_LRotate(T->lchild);		//对T的左子树作左旋操作
		_RRotate(T);				//对T作右旋操作
		return;
	}
	return;
}
//对以T为根结点的二叉排序树作右平衡处理，处理完毕后T指向新的树根结点
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_RightBalance(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * tr, *TempAVL;
	tr = T->rchild;					//tr指向T的右子树的根结点
	switch(tr->bf){					//根据tr的平衡因子，作相应调整
	case RH:						//新结点插在T的右孩子的右子树上，作左旋操作
		T->bf = tr->bf = EH;
		_LRotate(T);
		return ;
	case LH:						//新结点插在T的右孩子的左子树上，作两次旋转操作
		TempAVL = tr->lchild;		//TempAVL指向tr的左子树的根结点上
		switch(TempAVL->bf){
		case RH:
			tr->bf = EH;
			T->bf = LH;
			break;
			
		case EH:
			T->bf = tr->bf = EH;
			break;
		case LH:
			tr->bf = RH;
			T->bf = EH;
			break;
		}
		TempAVL->bf = EH;
		_RRotate(T->rchild);		//对T的右子树作右旋操作
		_LRotate(T);				//对T作左旋操作
		return;
	}
	return ;
}
//若在平衡二叉排序树中不存在关键字为key的结点，则插入一个数据值为e的新结点，并返回true,否则返回false
//若插入过程中导致平衡二叉排序树失衡，则作相应调整，使之保持平衡状态，布尔值bTaller反映T是否长高。
template< class ElemType,class KeyType>
bool AVL<ElemType,KeyType>::_Insert(AVLNode<ElemType,KeyType> * &T,ElemType e,KeyType key,bool &bTaller)
{
	if(!T){									//若T为空树，则插入新结点作为根，bTaller为true
		T = new AVLNode<ElemType,KeyType>;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		T->data = e;
		bTaller = true;
		return true;
	}
	if(T->data == key)						//平衡二叉排序树中已存在和key相同关键字的结点，不再插入，返回false
		return false;
	if(T->data > key){						//在T的左子树中进行搜索
		if(!_Insert(T->lchild,e,key,bTaller))
			return false;
		if(bTaller){						//在T的左子树中插入新结点并使得左子树长高
			switch(T->bf){					//根据T的平衡因子作相应处理
			case LH:						//原本左子树高，则作左平衡处理
				_LeftBalance(T);
				bTaller = false;
				return true;
			case EH:						//原本等高，无需作平衡处理，整棵树长高
				bTaller = true;
				T->bf = LH;
				return true;
			case RH:						//原本右子树高，无需作平衡处理，整棵树未长高
				T->bf = EH;
				bTaller = false;
				return true;
			}
		}
	}else{									//在T的右子树中进行搜索
		if(!_Insert(T->rchild,e,key,bTaller))
			return false;
		if(bTaller){						//在T的右子树中插入新结点并使得右子树长高
			switch(T->bf){					//根据T的平衡因子作相应处理
			case LH:						//原本左子树高，无需作平衡处理，整棵树未长高
				T->bf = EH;
				bTaller = false;
				return true;
			case EH:						//原本等高，无需作平衡处理，整棵树长高
				T->bf = RH;
				bTaller = true;
				return true;
			case RH:						//原本右子树高，则作右平衡处理
				_RightBalance(T);
				bTaller = false;
				return true;
			}
		}
	}
	return true;
}
//若在平衡二叉排序树中存在和key有相同关键字的结点，则删除，并返回true,否则返回false
//若删除过程中导致平衡二叉排序树失衡，则作相应调整，使之保持平衡状态，布尔值bTaller反映T是否缩短。
template< class ElemType,class KeyType>
bool AVL<ElemType,KeyType>::_Delete(AVLNode<ElemType,KeyType> * &T,KeyType key,bool &bShorter)
{
	KeyType TempData;
	AVLNode<ElemType,KeyType> * tr;
	if(!T)											//T为空树，无法删除，返回false
		return false;
	if(T->data == key){								//找到数据值为key的结点T
		if(T->lchild == NULL && T->rchild == NULL){	//若T为叶子结点，删除
			delete T;
			T = NULL;
			bShorter = true;
			return true;
		}
		else if(T->lchild){							//若T无右子树
			tr = T->lchild;							//tr作为T的左子树的根结点
			while(tr->rchild)						//沿着tr的右子树分支一直找到最右端的结点
				tr = tr->rchild;
			TempData = T->data;
			T->data = tr->data;
			tr->data = TempData;
			if(!_Delete(T->lchild,key,bShorter))
				return false;
			if(bShorter){							//在T的左子树中删除结点	
				switch(T->bf){						//根据T的平衡因子作相应处理
				case LH:							//原本左子树高，则无需作平衡处理，树高缩短
					T->bf = EH;
					bShorter = true;
					return true;
				case EH:							//原本等高，则无需作平衡处理，树高未缩短	
					T->bf = RH;
					bShorter = false;
					return true;
				case RH:							//原本右高
					if(T->rchild->bf == EH)
						bShorter = false;
					else
						bShorter = true;
					_RightBalance(T);				//作右平衡处理	
					return true;
				}
			}
		}else if(T->rchild){						//若T无左子树
			tr = T->rchild;							//tr作为T的右子树的根结点
			while(tr->lchild)
				tr = tr->lchild;					//沿着tr的左子树分支一直找到最左端的结点
			TempData = T->data;
			T->data = tr->data;
			tr->data = TempData;
			if(!_Delete(T->rchild,key,bShorter))
				return false;
			if(bShorter){							//在T的右子树中删除结点
				switch(T->bf){						//根据T的平衡因子作相应处理
				case RH:							//原本右子树高，则无需作平衡处理，树高缩短
					bShorter = true;
					T->bf = EH;
					return true;
				case EH:							//原本等高，则无需作平衡处理，树高未缩短
					bShorter = false;
					T->bf = LH;
					return true;
				case LH:							//原本左高
					if(T->lchild->bf == EH)
						bShorter = false;
					else
						bShorter = true;
					_LeftBalance(T);				//作左平衡处理
					return true;
				}
			}
		}
	}else if(T->data > key){						//在T的左子树中搜索，若找到则删除
		if(!_Delete(T->lchild,key,bShorter))
			return false;
		if(bShorter){
			switch(T->bf){
			case LH:
				T->bf = EH;
				bShorter = true;
				return true;
			case EH:
				T->bf = RH;
				bShorter = false;
				return true;
			case RH:
				if(T->rchild->bf == EH)
					bShorter = false;
				else
					bShorter = true;
				_RightBalance(T);
				return true;
			}
		}
	}else{											//在T的右子树中搜索，若找到则删除
		if(!_Delete(T->rchild,key,bShorter))
			return false;
		if(bShorter){
			switch(T->bf){
			case RH:
				bShorter = true;
				T->bf = EH;
				return true;
			case EH:
				bShorter = false;
				T->bf = LH;
				return true;
			case LH:
				if(T->lchild->bf == EH)
					bShorter = false;
				else
					bShorter = true;
				_LeftBalance(T);
				return true;
			}
		}
	}
	return true;
}
//在以T为根的平衡二叉排序树中查找关键字为key的结点，若找到则返回该结点指针，否则返回NULL
template< class ElemType,class KeyType>
AVLNode<ElemType,KeyType> * AVL<ElemType,KeyType>::_Search(AVLNode<ElemType,KeyType> * T,KeyType key)
{
	if(!T)
		return NULL;
	if(T->data == key)
		return T;
	if(T->data > key )
		return _Search(T->lchild,key);
	else
		return _Search(T->rchild,key);
}
//获取平衡二叉排序树的深度
template< class ElemType,class KeyType>
int AVL<ElemType,KeyType>::_GetDepth(AVLNode<ElemType,KeyType>* T)
{
	if(!T)
		return 0;
	switch(T->bf){
	case LH:
		return (1 + _GetDepth(T->lchild));
	case RH:
		return (1 + _GetDepth(T->rchild));
	default:
		return (1 + _GetDepth(T->lchild));
	}
}
//中序遍历二叉树     
template <class ElemType,class KeyType>
void AVL<ElemType,KeyType> ::_InorderTraverse(AVLNode<ElemType,KeyType>* T)
{  
    if(T){
        _InorderTraverse(T->lchild);
        //cout << T->data<<" ";
		T->data;
        _InorderTraverse(T->rchild);
        }  
}
#endif