package uba.algo3.tp2;


public class Baldoza implements Comparable<Baldoza> {

	private int piso;
	private int metros;
	
	
	public Baldoza( int i, int j ) {
		setPiso( i );
		setMetros( j );
	}

	public int compareTo( Baldoza o ) {
		return getPiso() != o.getPiso() ? 
		         getPiso() - o.getPiso() : 
		         getMetros() - o.getMetros();
	}

	public String toString() {
		return "(" + getPiso() + " " + getMetros() + ")";
	}

   public int getPiso() {              return piso;      }
   public void setPiso( int p ) {      piso = p;         }

   public int getMetros() {            return metros;    }
   public void setMetros( int m ) {    metros = m;       }
	
}
