#!/usr/bin/env python
# Author: carlos.pantelides@gmail.com
 
import re
import sys
import urllib
import urlparse
from BeautifulSoup import BeautifulSoup

def showLinks(title,links):
   if (links):
      print title
      for link in sorted(set(links)):
         repetitions = str(links.count(link))
         print repetitions + "   " + link
      print 

def checkLinks(title,links):
    if (links):
      print title
      for link in sorted(set(links)):
         repetitions = str(links.count(link))
         page = urllib.urlopen(link)
         text = page.read()
         page.close()
         if (re.search('Este tema no existe',text)):
            status = ' FAIL '
         else:
            status = ' OK   '     
         print repetitions + status + link
      print

def processLandingPage(url):
   internalLinks = []
   externalLinks = []
   othersLinks = []
   mailLinks = []
   unknownLinks = []

   page = urllib.urlopen(url)
   text = page.read()
   page.close()

   soup = BeautifulSoup(text)

   for tag in soup.findAll('a', href=True):
      tag['href'] = str(urlparse.urljoin(url, tag['href']))
      if ('http' == tag['href'][0:4]):
         if ('http://proyecto-ciaa.com.ar' == tag['href'][0:27] or 
             'http://www.proyecto-ciaa.com.ar' == tag['href'][0:31] ):
            internalLinks.append(tag['href'])
         else:
            if (re.search('ciaa',tag['href'], re.IGNORECASE)):
               externalLinks.append(tag['href'])
            else:
               othersLinks.append(tag['href'])
      elif ('mailto' == tag['href'][0:6]):
         mailLinks.append(tag['href'])
      else:
         unknownLinks.append(tag['href'])

   showLinks("Links desconocidos", unknownLinks)
   showLinks("Direcciones de email", mailLinks)
   showLinks("Links a otros", othersLinks)
   showLinks("Links externos", externalLinks)
   checkLinks("Links internos", internalLinks)

def main():
   if len(sys.argv) == 1:
      print "Proyecto CIAA: verificador de calidad de links"
      print "Uso: %s URL [URL]..." % sys.argv[0]
      print "Ejemplo:"
      print "   ./verificarLinks.py http://proyecto-ciaa.com.ar"

      sys.exit(-1)
   for url in sys.argv[1:]:
      processLandingPage(url)
 
if __name__ == "__main__":
   main()
