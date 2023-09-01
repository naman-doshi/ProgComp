f = open('image.svg', 'w')

template = '''<?xml version="1.0" encoding="iso-8859-1"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 20001102//EN" 
 "http://www.w3.org/TR/2000/CR-SVG-20001102/DTD/svg-20001102.dtd"> 

<svg width="1000" height="800"
     xmlns="http://www.w3.org/2000/svg"
     xmlns:xlink="http://www.w3.org/1999/xlink">

<defs>
  <style type="text/css">
  <![CDATA[

    text.C { text-anchor:middle; }   /* centred */
    text.R { text-anchor:end; }      /* right-justified */
    text.title { font-size:16px; font-family:Arial,Helvetica,sansserif; font-weight:bold; }

    .bar { stroke:#888888; stroke-width:0.5px; }
    .unordered { fill:#E7CACA; stroke:#B54040; }
    .bg {fill:#888888;}
    .shuffled { fill:#E7CACA;}
    .home {fill:#DEE7BE;}
    .selected {fill:#FFFF66;}
    .error {fill:#F72424;}

    .tex {font-size: 32px; font-weight:bold; }

    .sep { stroke:#444444; stroke-width:0.8px; stroke-dasharray:5,3; }
    .border { stroke: #AAAAAA; stroke-width:3px; fill:#FFFFF0; }

    .pink { fill:#FFB5DC; }
    .skyblue { fill:#87CEEB; }
  ]]>
  </style>

  <!-- define an equilateral triangle centred at the origin with base 10px long. 8.66 = 10sind(60) -->
  <g id="triangle">
    <path  d="M0,-4.33 l-5,8.66 h10z" />  <!-- Moveto; relative lineto; relative horizontal lineto; close path -->
  </g>

  <!-- Adapted from http://ledrug.wordpress.com/2010/09/30/learning-svg-lesson-2/ -->

  <filter id="bevel" x0="-50%" y0="-50%" width="200%" height="200%">
    <feGaussianBlur in="SourceAlpha" stdDeviation="2" result="blur"/>
    <feOffset dy="-1" dx="-1"/>
    <feComposite in2="SourceAlpha" operator="arithmetic"
            k2="-1" k3="1" result="hlDiff"/>
    <feFlood flood-color="black" flood-opacity="1.0"/>
    <feComposite in2="hlDiff" operator="in"/>
    <feComposite in2="SourceGraphic" operator="over" result="withGlow"/>

    <feOffset in="blur" dy="2" dx="2"/>
    <feComposite in2="SourceAlpha" operator="arithmetic"
            k2="-1" k3="1" result="shadowDiff"/>
    <feFlood flood-color="white" flood-opacity="0.7"/>
    <feComposite in2="shadowDiff" operator="in"/>
    <feComposite in2="withGlow" operator="over"/>
  </filter>

</defs>
<rect class="border" x="0" y="0" width="1000" height="800" />
'''

f.write(template)

width = 1000
height = 800

def conclude():
    f.write('</svg>')
    f.close()

def addTitle(title):
    f.write(f'<text class="title C" x="{width/2}" y="{height/12}">{title}</text>\n')

def printIndents(numIndents):
    for i in range(numIndents):
        f.write('  ')

class animation:
    # attributeName can be anything: x, y, fill, stroke etc.
    def __init__(self, attributeName, begin, duration, to, fill="freeze"):
        self.attributeName = attributeName
        self.fill = fill
        self.begin = begin
        self.duration = duration
        self.to = to
    
    def generate(self):
        return f'<animate attributeName="{self.attributeName}" fill="{self.fill}" begin="{self.begin}s" dur="{self.duration}s" to="{self.to}" />\n'

class animateTransform:
    def __init__(self, attributeName, type, begin, dur, from_, to, repeatCount="", fill="freeze"):
        self.attributeName = attributeName
        self.type_ = type
        self.to = to
        self.dur = dur
        self.repeatCount = repeatCount
        self.fill = fill
        self.begin = begin
        self.from_ = from_
    
    def generate(self):
        if self.repeatCount == "":
            return f'<animateTransform attributeName="{self.attributeName}" type="{self.type_}" begin="{self.begin}s" from="{self.from_}" to="{self.to}" dur="{self.dur}s" fill="{self.fill}" />\n'
            

class line:
    def __init__(self, x1, y1, x2, y2, opacity="", class_=[], animations=[]):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.opacity = opacity
        self.class_ = class_
        self.animations = animations
    
    def addAnimation(self, anim):
        self.animations.append(anim)

    def deleteClass(self, clas):
        self.class_.remove(clas)

    def addClass(self, clas):
        self.class_.append(clas)

    def draw(self):
        f.write(f'<line class="{" ".join(self.class_)}" x1="{self.x1}" y1="{self.y1}" x2="{self.x2}" y2="{self.y2}" opacity="{self.opacity}" >\n')
        for anim in self.animations:
            printIndents(1)
            f.write(anim.generate())
        f.write('</line>\n')

class rectangle:
    def __init__(self, x, y, width, height, id="", class_=[], filter="", animations=[]):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.class_ = class_
        self.animations = animations
        self.id = id
        self.filter = filter
    
    def addAnimation(self, anim):
        self.animations.append(anim)

    def deleteClass(self, clas):
        self.class_.remove(clas)

    def addClass(self, clas):
        self.class_.append(clas)

    def draw(self):
        f.write(f'<rect id="{self.id}" class="{" ".join(self.class_)}" filter="{self.filter}" x="{self.x}" y="{self.y}" width="{self.width}" height="{self.height}" >\n')
        for anim in self.animations:
            printIndents(1)
            f.write(anim.generate())
        f.write('</rect>\n')

class circle:
    def __init__(self, cx, cy, r, id="", class_=[], animations=[]):
        self.cx = cx
        self.cy = cy
        self.r = r
        self.class_ = class_
        self.animations = animations
        self.id = id
    
    def addAnimation(self, anim):
        self.animations.append(anim)

    def deleteClass(self, clas):
        self.class_.remove(clas)

    def addClass(self, clas):
        self.class_.append(clas)

    def draw(self):
        f.write(f'<circle id="{self.id}" class="{" ".join(self.class_)}" cx="{self.cx}" cy="{self.cy}" r="{self.r}" >\n')
        for anim in self.animations:
            printIndents(1)
            f.write(anim.generate())
        f.write('</circle>\n')

class text:
    def __init__(self, x, y, text, id="", class_=[], animations=[]):
        self.x = x
        self.y = y
        self.text = text
        self.class_ = class_
        self.animations = animations
        self.id = id
    
    def addAnimation(self, anim):
        self.animations.append(anim)

    def deleteClass(self, clas):
        self.class_.remove(clas)

    def addClass(self, clas):
        self.class_.append(clas)

    def draw(self):
        f.write(f'<text id="{self.id}" class="{" ".join(self.class_)}" x="{self.x}" y="{self.y}" >\n')
        for anim in self.animations:
            printIndents(1)
            f.write(anim.generate())
        f.write(f'{self.text}</text>\n')

class ellipse:
    def __init__(self, cx, cy, rx, ry, id="", class_=[], animations=[]):
        self.cx = cx
        self.cy = cy
        self.rx = rx
        self.ry = ry
        self.class_ = class_
        self.animations = animations
        self.id = id
    
    def addAnimation(self, anim):
        self.animations.append(anim)

    def deleteClass(self, clas):
        self.class_.remove(clas)

    def addClass(self, clas):
        self.class_.append(clas)

    def draw(self):
        f.write(f'<ellipse id="{self.id}" class="{" ".join(self.class_)}" cx="{self.cx}" cy="{self.cy}" rx="{self.rx}" ry="{self.ry}" >\n')
        for anim in self.animations:
            printIndents(1)
            f.write(anim.generate())
        f.write('</ellipse>\n')


class group:
    def __init__(self, x, y, id="", class_=[], animations=[], shapes=[]):
        self.x = x
        self.y = y
        self.class_ = class_
        self.animations = animations
        self.id = id
        self.shapes = shapes
    
    def addAnimation(self, anim):
        self.animations.append(anim)

    def deleteClass(self, clas):
        self.class_.remove(clas)

    def addClass(self, clas):
        self.class_.append(clas)

    def addShape(self, shape):
        self.shapes.append(shape)
    
    def draw(self):
        f.write(f'<g id="{self.id}" class="{" ".join(self.class_)}" transform="translate({self.x}, {self.y})" >\n')
        for anim in self.animations:
            printIndents(1)
            f.write(anim.generate())
        for shape in self.shapes:
            printIndents(1)
            shape.draw()
        f.write('</g>\n')

    
    
