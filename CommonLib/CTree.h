#ifndef _AVL_H_
#define _AVL_H_
#include <iostream>
#define LH	1		//���
#define EH	0		//�ȸ�
#define RH	-1		//�Ҹ�
//ƽ��������������ṹ 
template <class ElemType,class KeyType>
struct AVLNode{
    ElemType data;					        //���������
    AVLNode<ElemType,KeyType> *lchild;		//�������
    AVLNode<ElemType,KeyType> *rchild;		//����Һ���
	int bf;							        //���ƽ������
};
//ƽ�������������
template< class ElemType,class KeyType>
class AVL{
public:
	AVL ();				
	~AVL ( );
	AVLNode<ElemType,KeyType> *Root() const{return m_T;};//����ƽ��������ĸ�ָ��
	AVLNode<ElemType,KeyType> *FindMin(AVLNode<ElemType,KeyType> *node) const;
	AVLNode<ElemType,KeyType> *FindMax(AVLNode<ElemType,KeyType> *node) const;
	bool Insert(const ElemType & e,const KeyType & key);//ƽ������������в���ؼ���Ϊkey��Ԫ��e
	bool Delete(const KeyType & key);//ƽ�������������ɾ���ؼ���Ϊkey��Ԫ��
	AVLNode<ElemType,KeyType>* Search(const KeyType & key);//ƽ������������в����Ƿ���ڹؼ���Ϊkey��Ԫ��
	int GetDepth();	//��ƽ����������������
	void InorderTraverse();	//�������ƽ�����������
private:
	AVLNode<ElemType,KeyType> * m_T;//ƽ�������������ָ��
	void _Destroy(AVLNode<ElemType,KeyType> * &T);//����ƽ�����������
	void _RRotate(AVLNode<ElemType,KeyType> * &T);//��������
	void _LRotate(AVLNode<ElemType,KeyType> * &T);//��������
	void _LeftBalance(AVLNode<ElemType,KeyType> * &T);//��ƽ�⴦��
	void _RightBalance(AVLNode<ElemType,KeyType> * &T);	//��ƽ�⴦��
	bool _Insert(AVLNode<ElemType,KeyType> * &T,ElemType e,KeyType key,bool &bTaller);//ƽ������������в���ؼ���Ϊkey��Ԫ�أ�������ƽ��״̬
	bool _Delete(AVLNode<ElemType,KeyType> * &T,KeyType key,bool &bShorter);//ƽ�������������ɾ���ؼ���ΪKey��Ԫ�أ�������ƽ��״̬
	AVLNode<ElemType,KeyType>* _Search(AVLNode<ElemType,KeyType>* T,KeyType key);//ƽ������������в����Ƿ���ڹؼ���key
	int  _GetDepth(AVLNode<ElemType,KeyType>* T);//��ƽ����������������
	void _InorderTraverse(AVLNode<ElemType,KeyType>* T);//�������������
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
//��ƽ������������в��ҹؼ���Ϊkey��Ԫ���Ƿ����
template< class ElemType,class KeyType>
AVLNode<ElemType,KeyType>* AVL<ElemType,KeyType>::Search(const KeyType & key)
{
	return _Search(m_T,key);
}
// ��ʼ����: ƽ�����������T���ڡ��������: ����T�����     
template <class ElemType,class KeyType> 
int AVL<ElemType,KeyType>::GetDepth()
{
    return _GetDepth(m_T);
}
// �������������        
template <class ElemType,class KeyType>
void AVL <ElemType,KeyType>::InorderTraverse()
{
    _InorderTraverse(m_T);
} 
//����ƽ�����������
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
//����TΪ���Ķ���������������������������Tָ���µ��������
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_RRotate(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * TempAVL;
	TempAVL = T->lchild;			//TempAVLָ��T���������ĸ����
	T->lchild = TempAVL->rchild;	//TempAVL���������ҽ���ΪT��������
	TempAVL->rchild = T;			
	T = TempAVL;					//Tָ���µ��������
}
//����TΪ���Ķ���������������������������Tָ���µ��������
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_LRotate(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * TempAVL;
	TempAVL = T->rchild;			//TempAVLָ��T���������ĸ����
	T->rchild = TempAVL->lchild;	//TempAVL���������ҽ���ΪT��������
	TempAVL->lchild = T;
	T = TempAVL;					//Tָ���µ��������
}
//����TΪ�����Ķ�������������ƽ�⴦��������Ϻ�Tָ���µ��������
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_LeftBalance(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * tr, * TempAVL;
	tr = T->lchild;					//trָ��T���������ĸ����
	switch(tr->bf){					//����tr��ƽ�����ӣ�����Ӧ����
	case LH:						//�½�����T�����ӵ��������ϣ�����������
		T->bf = EH;
		_RRotate(T);
		tr->bf = EH;
		return;
	case RH:						//�½�����T�����ӵ��������ϣ���������ת����
		TempAVL = tr->rchild;		//TempAVLָ��tr���������ĸ������
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
		_LRotate(T->lchild);		//��T������������������
		_RRotate(T);				//��T����������
		return;
	}
	return;
}
//����TΪ�����Ķ�������������ƽ�⴦��������Ϻ�Tָ���µ��������
template< class ElemType,class KeyType>
void AVL<ElemType,KeyType>::_RightBalance(AVLNode<ElemType,KeyType> * &T)
{
	AVLNode<ElemType,KeyType> * tr, *TempAVL;
	tr = T->rchild;					//trָ��T���������ĸ����
	switch(tr->bf){					//����tr��ƽ�����ӣ�����Ӧ����
	case RH:						//�½�����T���Һ��ӵ��������ϣ�����������
		T->bf = tr->bf = EH;
		_LRotate(T);
		return ;
	case LH:						//�½�����T���Һ��ӵ��������ϣ���������ת����
		TempAVL = tr->lchild;		//TempAVLָ��tr���������ĸ������
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
		_RRotate(T->rchild);		//��T������������������
		_LRotate(T);				//��T����������
		return;
	}
	return ;
}
//����ƽ������������в����ڹؼ���Ϊkey�Ľ�㣬�����һ������ֵΪe���½�㣬������true,���򷵻�false
//����������е���ƽ�����������ʧ�⣬������Ӧ������ʹ֮����ƽ��״̬������ֵbTaller��ӳT�Ƿ񳤸ߡ�
template< class ElemType,class KeyType>
bool AVL<ElemType,KeyType>::_Insert(AVLNode<ElemType,KeyType> * &T,ElemType e,KeyType key,bool &bTaller)
{
	if(!T){									//��TΪ������������½����Ϊ����bTallerΪtrue
		T = new AVLNode<ElemType,KeyType>;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		T->data = e;
		bTaller = true;
		return true;
	}
	if(T->data == key)						//ƽ��������������Ѵ��ں�key��ͬ�ؼ��ֵĽ�㣬���ٲ��룬����false
		return false;
	if(T->data > key){						//��T���������н�������
		if(!_Insert(T->lchild,e,key,bTaller))
			return false;
		if(bTaller){						//��T���������в����½�㲢ʹ������������
			switch(T->bf){					//����T��ƽ����������Ӧ����
			case LH:						//ԭ���������ߣ�������ƽ�⴦��
				_LeftBalance(T);
				bTaller = false;
				return true;
			case EH:						//ԭ���ȸߣ�������ƽ�⴦������������
				bTaller = true;
				T->bf = LH;
				return true;
			case RH:						//ԭ���������ߣ�������ƽ�⴦��������δ����
				T->bf = EH;
				bTaller = false;
				return true;
			}
		}
	}else{									//��T���������н�������
		if(!_Insert(T->rchild,e,key,bTaller))
			return false;
		if(bTaller){						//��T���������в����½�㲢ʹ������������
			switch(T->bf){					//����T��ƽ����������Ӧ����
			case LH:						//ԭ���������ߣ�������ƽ�⴦��������δ����
				T->bf = EH;
				bTaller = false;
				return true;
			case EH:						//ԭ���ȸߣ�������ƽ�⴦������������
				T->bf = RH;
				bTaller = true;
				return true;
			case RH:						//ԭ���������ߣ�������ƽ�⴦��
				_RightBalance(T);
				bTaller = false;
				return true;
			}
		}
	}
	return true;
}
//����ƽ������������д��ں�key����ͬ�ؼ��ֵĽ�㣬��ɾ����������true,���򷵻�false
//��ɾ�������е���ƽ�����������ʧ�⣬������Ӧ������ʹ֮����ƽ��״̬������ֵbTaller��ӳT�Ƿ����̡�
template< class ElemType,class KeyType>
bool AVL<ElemType,KeyType>::_Delete(AVLNode<ElemType,KeyType> * &T,KeyType key,bool &bShorter)
{
	KeyType TempData;
	AVLNode<ElemType,KeyType> * tr;
	if(!T)											//TΪ�������޷�ɾ��������false
		return false;
	if(T->data == key){								//�ҵ�����ֵΪkey�Ľ��T
		if(T->lchild == NULL && T->rchild == NULL){	//��TΪҶ�ӽ�㣬ɾ��
			delete T;
			T = NULL;
			bShorter = true;
			return true;
		}
		else if(T->lchild){							//��T��������
			tr = T->lchild;							//tr��ΪT���������ĸ����
			while(tr->rchild)						//����tr����������֧һֱ�ҵ����Ҷ˵Ľ��
				tr = tr->rchild;
			TempData = T->data;
			T->data = tr->data;
			tr->data = TempData;
			if(!_Delete(T->lchild,key,bShorter))
				return false;
			if(bShorter){							//��T����������ɾ�����	
				switch(T->bf){						//����T��ƽ����������Ӧ����
				case LH:							//ԭ���������ߣ���������ƽ�⴦����������
					T->bf = EH;
					bShorter = true;
					return true;
				case EH:							//ԭ���ȸߣ���������ƽ�⴦������δ����	
					T->bf = RH;
					bShorter = false;
					return true;
				case RH:							//ԭ���Ҹ�
					if(T->rchild->bf == EH)
						bShorter = false;
					else
						bShorter = true;
					_RightBalance(T);				//����ƽ�⴦��	
					return true;
				}
			}
		}else if(T->rchild){						//��T��������
			tr = T->rchild;							//tr��ΪT���������ĸ����
			while(tr->lchild)
				tr = tr->lchild;					//����tr����������֧һֱ�ҵ�����˵Ľ��
			TempData = T->data;
			T->data = tr->data;
			tr->data = TempData;
			if(!_Delete(T->rchild,key,bShorter))
				return false;
			if(bShorter){							//��T����������ɾ�����
				switch(T->bf){						//����T��ƽ����������Ӧ����
				case RH:							//ԭ���������ߣ���������ƽ�⴦����������
					bShorter = true;
					T->bf = EH;
					return true;
				case EH:							//ԭ���ȸߣ���������ƽ�⴦������δ����
					bShorter = false;
					T->bf = LH;
					return true;
				case LH:							//ԭ�����
					if(T->lchild->bf == EH)
						bShorter = false;
					else
						bShorter = true;
					_LeftBalance(T);				//����ƽ�⴦��
					return true;
				}
			}
		}
	}else if(T->data > key){						//��T�������������������ҵ���ɾ��
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
	}else{											//��T�������������������ҵ���ɾ��
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
//����TΪ����ƽ������������в��ҹؼ���Ϊkey�Ľ�㣬���ҵ��򷵻ظý��ָ�룬���򷵻�NULL
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
//��ȡƽ����������������
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
//�������������     
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