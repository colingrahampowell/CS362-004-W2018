/*
 * CS362
 * Final Project: Part B
 * Sarah Maas (maass), Colin Powell (powelcol), Josh Williams (willijo4)
 */

import org.junit.Rule;
import org.junit.Test;
//import junit.framework.TestCase;
import org.junit.rules.ErrorCollector;
import org.hamcrest.CoreMatchers;

public class UrlValidatorTest {
	
	@Rule
	public ErrorCollector collector = new ErrorCollector();

	@Test
	public void testResultPairs() {
		
   		System.out.println("********Manual ResultPair Tests********");

		// ResultPair is broken...see ResultPair.java in src dir.
		ResultPair rp_true = new ResultPair("http://www.google.com", true);
		ResultPair rp_false = new ResultPair("foo", false);
				
		System.out.println("Testing ResultPair objects...");
		collector.checkThat("ResultPair reporting incorrect valid property", rp_true.valid, CoreMatchers.equalTo(true));
		collector.checkThat("ResultPair reporting incorrect valid property", rp_false.valid, CoreMatchers.equalTo(false));
		System.out.println("ResultPair testing complete.\n");
	}
	
	@Test
   	public void testManualTest() {

   		System.out.println("********Manual URL Tests********");
		
		System.out.println("Testing URLs...");
		String[] schemes = { "http", "https", "ftp" };
   		UrlValidator urlVal = new UrlValidator(schemes);
   	
   		// basic manual tests: 
   		// DEBUGGING NOTE: check UrlValidator line 282; schemes are converted to upper case 
   		// 		instead of lower case, as required by isValid...
   		// 		if ALLOW_ALL_SCHEMES flag is not set, this will cause all tests below to fail.
   		
   		collector.checkThat("expect basic http-based URL to be valid", 
   				  	urlVal.isValid("http://www.google.com"), CoreMatchers.equalTo(true));
			
	   	collector.checkThat("expect https to be recognized", 
	   				urlVal.isValid("https://www.google.com"), CoreMatchers.equalTo(true));

	 	collector.checkThat("expect ftp scheme to register as valid", 
 	 				urlVal.isValid("ftp://foo.bar.com/"), CoreMatchers.equalTo(true));
	   	
	 	//
	 	// now, testing with all schemes allowed
	 	//
	 	
	 	urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   		
	 	// DEBUGGING NOTE: line 318 in UrlValidator.java
	 	// 		UrlValidator.java written such that "http" cannot allow trailing ':' in authority.
	 	//		this should only be true for "file" schemes.
	 	
   		collector.checkThat("expect port numbers to be valid", 
   				  	urlVal.isValid("http://www.google.com:65530"), CoreMatchers.equalTo(true));
   		
   		collector.checkThat("expect query string to register as valid", 
   				  	urlVal.isValid("http://www.google.com?foo=bar&baz=bam"), CoreMatchers.equalTo(true));
   		
   		//RFC 1123: hostnames must be alphanumeric:
   		
   		collector.checkThat("expect numeric chars in hostname to register as valid", 
   				  	urlVal.isValid("http://www.g00gle.com"), CoreMatchers.equalTo(true));
   		
   		collector.checkThat("expect invalid TLD chars to register URL as invalid", 
   				  	urlVal.isValid("http://www.google.c!m"), CoreMatchers.equalTo(false));
   		
   		collector.checkThat("expect invalid hostname chars to register URL as invalid", 
   					urlVal.isValid("http://www.g!.com"), CoreMatchers.equalTo(false));
   		 		
   		// non-http protocols seem to be an issue, esp. with ALLOW_ALL_SCHEMES flag set:
   		// wrap in try/catch blocks to catch errors without terminating program
   		
   		try {
   			collector.checkThat("expect ftp scheme to register as valid", 
   					urlVal.isValid("ftp://ftp.filestorage.com"), CoreMatchers.equalTo(true));
   		} catch(Throwable err) {
   			collector.addError(err);
   		}
 	 	
 	 	try {
 	   		collector.checkThat("expect https to be recognized", 
   					urlVal.isValid("https://www.google.com"), CoreMatchers.equalTo(true));
 	 	} catch(Throwable err) {
 	 		collector.addError(err);
 	 	}	 	 	
	   
   		System.out.println("Manual testing complete\n");
   }
   
   @Test
   public void testYourFirstPartition() {	 
	 // Set a few valid URLs that should be valid, then test those

  	System.out.println("********First Partition: Valid URLs********");
		
	System.out.println("Testing valid URLs...");
	String[] schemes = { "http", "https", "ftp" };
	UrlValidator urlVal = new UrlValidator(schemes);
	
	collector.checkThat("expect basic http-based URL to be valid", 
	  	urlVal.isValid("http://www.google.com"), CoreMatchers.equalTo(true));
	collector.checkThat("expect basic http-based URL to be valid", 
		urlVal.isValid("https://www.google.com"), CoreMatchers.equalTo(true));
	collector.checkThat("expect basic http-based URL to be valid", 
		urlVal.isValid("ftp://foo.bar.com/"), CoreMatchers.equalTo(true));

	
	urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	collector.checkThat("Authority should be correct", 
		urlVal.isValid("http://www.google.com:65530"), CoreMatchers.equalTo(true));
	collector.checkThat("Path should be valid", 
		urlVal.isValid("http://www.google.com/mail"), CoreMatchers.equalTo(true));
	collector.checkThat("Query should be valid", 
			urlVal.isValid("http://www.google.com?foo=bar&baz=bam"), CoreMatchers.equalTo(true));
	collector.checkThat("URL fragment should be valid", 
		urlVal.isValid("http://www.google.com/mail#two"), CoreMatchers.equalTo(true));
 	
  	System.out.println("First Partition Complete\n");
		
   }
   
   @Test
   public void testYourSecondPartition() {
	  	System.out.println("********Second Partition: Invalid URLs********");
		
		System.out.println("Testing invalid URLs...");
		String[] schemes = { "http", "https", "ftp" };
		UrlValidator urlVal = new UrlValidator(schemes);

	  	// Test URLs with invalid scheme
	  	collector.checkThat("expect basic http-based URL to be valid", 
			  	urlVal.isValid("httcs://www.google.com"), CoreMatchers.equalTo(false));	   

	  	urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	  	
	  	// Test URLs with invalid authority
	  	collector.checkThat("Testing with invalid authority", 
			  	urlVal.isValid("https://www.googlrcom:66666666"), CoreMatchers.equalTo(false));	   
	   
	  	// Test URLs with invalid path
		collector.checkThat("Testing with invalid path", 
			  	urlVal.isValid("https://www.google.com/ooop"), CoreMatchers.equalTo(false));	   
	   
	  	// Test URLs with invalid query
		collector.checkThat("Testing with invalid query", 
			  	urlVal.isValid("http://www.google.com?foo$bar*baz-bam"), CoreMatchers.equalTo(false));	   
	   
	  	// Test URLs with invalid fragment
		collector.checkThat("Testing with invalid query", 
			  	urlVal.isValid("https://www.google.com#ll"), CoreMatchers.equalTo(false));
	  	
	  	System.out.println("Second Partition Complete\n");
   }
   //You may need to create more test cases for your Partitions
   
   //@Test
   /*public void testIsValid() {
	   //You can use this function for programming based testing

   }*/

}
