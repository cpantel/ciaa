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
	 print repetitions + '       ' + link
      print 

def checkLinks(title,links):
   if (links):
      print title
      for link in sorted(set(links)):
         try:
            repetitions = str(links.count(link))
            code,text = readPage(link)
            if (code == 200):
               if (re.search('Este tema no existe',text)):
                  status = ' FAIL  '
               else:
                  status = ' OK    '     
            else:
               status = ' ' + str(code)  + '   '
            print repetitions + status + link
         except IOError:
            print 'No se puedo verificar ' + link

def readPage(url):
   page = urllib.urlopen(url)
   text = page.read()
   code = page.getcode()
   page.close()
   return (code,text)

def isCiaaInternal(link):
   return ('http://proyecto-ciaa.com.ar' == link[0:27] or
           'http://www.proyecto-ciaa.com.ar' == link[0:31] )

def isCiaaExternal(link):
   return (re.search('ciaa',link, re.IGNORECASE) )

def isMail(link):
   return ('mailto' == link[0:6])

def isHttp(link):
   return ('http' == link[0:4])

def cleanLink(url,link):
   link = str(urlparse.urljoin(url, link))
   return re.sub('&.*$', '', link)

def processLandingPage(url):
   internalLinks = []
   externalLinks = []
   othersLinks = []
   mailLinks = []
   unknownLinks = []
   try:
      code,text = readPage(url)
      soup = BeautifulSoup(text)

      for tag in soup.findAll('a', href=True):
         link = cleanLink(url, tag['href'])
         if (isHttp(link)):
            if ( isCiaaInternal(link)):
               internalLinks.append(link)
            else:
               if (isCiaaExternal(link)):
                  externalLinks.append(link)
               else:
                  othersLinks.append(link)
         elif (isMail(link)):
            mailLinks.append(link)
         else:
            unknownLinks.append(link)

      showLinks("Links desconocidos", unknownLinks)
      showLinks("Direcciones de email", mailLinks)
      showLinks("Links a otros", othersLinks)
      showLinks("Links externos", externalLinks)
      checkLinks("Links internos", internalLinks)
   except IOError:
      print 'No se puedo abrir ' + url


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
