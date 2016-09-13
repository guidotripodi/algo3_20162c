package uba.algo3.tp2;

import static org.junit.Assert.assertEquals;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import org.junit.Test;

public class TestEj1 {

   @Test
   public void fileWritingRunTest() throws IOException {
      // Con este test se lee el archivo de entrada proporcioando por la catedra 
      //    y se genera la salida
      BufferedReader is = new BufferedReader( new InputStreamReader( getClass().getResourceAsStream( "Tp2Ej1.in" ) ) );
      BufferedWriter os = new BufferedWriter( new FileWriter( getClass().getResource( "" ).getPath() + "Tp2Ej1.test.out" ) );
      
      String line;
      while ( ( line = is.readLine() ) != null ) {
         os.append( run( line, is.readLine() ) ).append( '\n' );
      }
      os.close();
      
   }

   @Test
   public void fileTestingRunTest() throws IOException {
      // Con este test se compara un archivo de entrada con el formato de la catedra 
      //    contra otro archivo con valores esperados
      BufferedReader source  = new BufferedReader( new InputStreamReader( getClass().getResourceAsStream( "Tp2Ej1.in" ) ) );
      BufferedReader control = new BufferedReader( new InputStreamReader( getClass().getResourceAsStream( "Tp2Ej1.out" ) ) );
      
      String line;
      while ( ( line = source.readLine() ) != null ) {
         assertEquals( control.readLine(), run( line, source.readLine() ) );
      }
      
   }

   private String run( String a, String b ) {
      return String.valueOf( new Ejercicio1( Integer.parseInt( a ), parsePortales( b ) ).solve() );
   }

	private List<Portal> parsePortales( String line ) {
      ArrayList portales = new ArrayList();

      StringTokenizer st = new StringTokenizer( line, ";" );
      while ( st.hasMoreTokens() ) {
         StringTokenizer portal = new StringTokenizer( st.nextToken(), " " );
         portales.add( new Portal( Integer.parseInt( portal.nextToken() ), 
                                   Integer.parseInt( portal.nextToken() ) ) );
      }

      return portales;
   }

   @Test
	public void test1() {
		ArrayList portales = new ArrayList();
		portales.add( new Portal( 0, 10 ) );
		
		assertEquals( 1, new Ejercicio1( 10, portales ).solve() );
	}

   @Test
   public void test2() {
      ArrayList portales = new ArrayList();
      portales.add( new Portal( 0, 6 ) );
      portales.add( new Portal( 2, 7 ) );
      portales.add( new Portal( 3, 8 ) );
      portales.add( new Portal( 6, 10 ) );

      assertEquals( 2, new Ejercicio1( 10, portales ).solve() );
   }

   @Test
   public void test2b() {
      ArrayList portales = new ArrayList();
      portales.add( new Portal( 0, 3 ) );
      portales.add( new Portal( 3, 10 ) );
      portales.add( new Portal( 3, 5 ) );
      portales.add( new Portal( 5, 6 ) );
      portales.add( new Portal( 6, 10 ) );

      assertEquals( 4, new Ejercicio1( 10, portales ).solve() );
   }

   @Test
   public void test3() {
      ArrayList portales = new ArrayList();
      portales.add( new Portal( 0, 1 ) );
      portales.add( new Portal( 1, 2 ) );
      portales.add( new Portal( 2, 10 ) );

      assertEquals( 3, new Ejercicio1( 10, portales ).solve() );
   }
   @Test
   public void test3i() {
      ArrayList portales = new ArrayList();
      portales.add( new Portal( 2, 10 ) );
      portales.add( new Portal( 1, 2 ) );
      portales.add( new Portal( 0, 1 ) );

      assertEquals( 3, new Ejercicio1( 10, portales ).solve() );
   }

	@Test
	public void test4() {
		ArrayList portales = new ArrayList();
		portales.add( new Portal( 3, 8 ) );
		portales.add( new Portal( 6, 10 ) );
		portales.add( new Portal( 2, 7 ) );
		portales.add( new Portal( 0, 6 ) );

		assertEquals( 2, new Ejercicio1( 10, portales ).solve() );
	}
}