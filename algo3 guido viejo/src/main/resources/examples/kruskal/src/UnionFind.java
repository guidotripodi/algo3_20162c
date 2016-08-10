package uba.algo3.kruskal;

import java.util.ArrayList;

public class UnionFind {

   private ArrayList<Integer> _parent = new ArrayList<Integer>();
   private ArrayList<Integer> _rank = new ArrayList<Integer>();


    // COMPLETAR !
   public UnionFind( int n ) {
       for (int i = 0; i < n; i++) {
            _parent.add(i);
            _rank.add(0); 
       }
      // Crea un bosque de n nodos.
      // Cada nodo tiene rank 0 al principio.
      // Cada nodo es su propio padre el principio.
   }

   public final int findSet( int i ) {
        if (_parent.get(i) != i){
            _parent.set(i, findSet(_parent.get(i)));
        }
        return _parent.get(i);
      // Si el padre es el mismo nodo, devuelvo ese nodo.
      // Si no, llamo recursivamente hacia el padre, y actualizo el padre del
      // nodo.
   }

   public final boolean isSameSet( int i, int j ) {
       return findSet(i) == findSet(j);
      // Devuelve si 2 nodos pertenecen o no al mismo conjunto.
   }

   public final void unionSet( int i, int j ) {
       int reprI = findSet(i);
       int reprJ = findSet(j);
       if (_rank.get(reprI) < _rank.get(reprJ)) {
           _parent.set(reprI, reprJ);
       } else {
           _parent.set(reprJ, reprI);
       }
       if (_rank.get(reprI) == _rank.get(reprJ)) {
           _rank.set(reprI, _rank.get(reprI) + 1);
       }
      // Si no pertenecen ya al mismo conjunto, los uno.
      // El que tenga menor rank pasara a formar parte del que tenga mayor rank.
      // Si ambos tienen igual rank es lo mismo cual uno a cual, pero debo
      // aumentar el rank del que sea el padre.
}
