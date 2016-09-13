package uba.algo3.tp2;

public class Portal<T extends Comparable> implements Comparable<Portal> {

	private T desde;
	private T hasta;

	public Portal( T d, T h ) {
		setDesde( d );
		setHasta( h );
	}

	public String toString() {
		return "P: " + getDesde().toString() + " " + getHasta().toString();
	}

   public int compareTo( Portal o ) {
      return o.getDesde() != getDesde()  ? getDesde().compareTo( o.getDesde() ) : getHasta().compareTo( o.getHasta() );
   }
   
   // Accessors
   public T getDesde() {               return desde;        }
   public void setDesde( T d ) {       desde = d;           }

   public T getHasta() {               return hasta;        }
   public void setHasta( T h ) {       hasta = h;           }
   
}