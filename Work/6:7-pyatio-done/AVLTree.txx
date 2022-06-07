//
// Implementation
//
template <typename E>					// constructor
  AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
  int AVLTree<E>::height(const TPos& v) const
    { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>					// set height utility
  void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
  }

template <typename E>					// is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
  }

template <typename E>					// get tallest grandchild
  typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
      if (height(zl.left()) >= height(zl.right()))
        return zl.left();
      else
        return zl.right();
    else 						// right child taller
      if (height(zr.right()) >= height(zr.left()))
        return zr.right();
      else
        return zr.left();
  }


//
// ToDo
//

template <typename E>                    // remove key k entry
  void AVLTree<E>::erase(const K& k) {
  // ToDo
  TPos v = this->finder(k, ST::root());
  if (Iterator(v) == ST::end())
  {
    std::cout << "Erase of Non Existent" << std::endl;
  }
  TPos w = this->eraser(v);
  rebalance(w);
  }

template <typename E>                    // insert (k,x)
  typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
  // ToDo
  TPos v = this->inserter(k, x);
  setHeight(v);
  rebalance(v);
  return Iterator(v);
  }
  
template <typename E>                    // rebalancing utility
  void AVLTree<E>::rebalance(const TPos& v) {
  // ToDo
  TPos z = v;
  while (!(z == ST::root()))
  {
    z = z.parent();
    setHeight(z);
    if (!isBalanced(z)) {
        TPos x = tallGrandchild(z);
        z = restructure(x);
        setHeight(z.left());
        setHeight(z.right());
        setHeight(z);
    }
  }
  }

template <typename E>                // Binary Search Tree Rotation
  typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v) {
  // ToDo
  TPos c = v; TPos b = v.parent(); TPos a = b.parent();
  TPos gp = a; TPos ggp = a.parent();

  if (a.v->elt.key() > b.v->elt.key())
  {
    if (b.v->elt.key() > c.v->elt.key())
    {
        TPos br;
        b.v->par = a.v->par;
        a.v->left = br.v = b.v->right;
        b.v->right = a.v;
        a.v->par = b.v;
        c.v->par = b.v;
        br.v->par = a.v;

        if (ggp.v->right == gp.v)
        {
            ggp.v->right = b.v;
        } else if (ggp.v->left == gp.v)
        {
            ggp.v->left = b.v;
        }
        return b;
    } else
    {
        TPos cr; TPos cl;
        c.v->par = a.v->par;
        a.v->left = cr.v = c.v->right;
        b.v->right = cl.v = c.v->left;
        c.v->right = a.v;
        c.v->left = b.v;
        b.v->par = c.v;
        a.v->par = c.v;
        cr.v->par = a.v;
        cl.v->par = b.v;
        if (ggp.v->right == gp.v)
        {
            ggp.v->right = c.v;
        }
        else if (ggp.v->left == gp.v)
        {
            ggp.v->left = c.v;
        }
        return c;
    }
  } else
  {
    if (b.v->elt.key() < c.v->elt.key())
    {
        TPos bl;
        b.v->par = a.v->par;
        a.v->right = bl.v = b.v->left;
        b.v->left = a.v;
        a.v->par = b.v;
        c.v->par = b.v;
        bl.v->par = a.v;
        if (ggp.v->right == gp.v)
        {
            ggp.v->right = b.v;
        } else if (ggp.v->left == gp.v)
        {
            ggp.v->left = b.v;
        }
        return b;
    } else
    {
        TPos cr; TPos cl;
        c.v->par = a.v->par;
        a.v->right = cl.v = c.v->left;
        b.v->left = cr.v = c.v->right;
        c.v->left = a.v;
        c.v->right = b.v;
        a.v->par = c.v;
        b.v->par = c.v;
        cl.v->par = a.v;
        cr.v->par = b.v;
        if (ggp.v->right == gp.v)
        {
            ggp.v->right = c.v;
        } else if (ggp.v->left == gp.v)
        {
            ggp.v->left = c.v;
        }
        return c;
    }
  }
}
