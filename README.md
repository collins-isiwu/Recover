# Recover

In this cs50 problem set, all the photos of a camera was accidentally deleted. Thankfully, in the computer world, “deleted” tends not to mean “deleted” so much as “forgotten.” Even though the camera insists that the card is now blank, we’re pretty sure that’s not quite true. I wrote a C program to RECOVER all the deleted pictures from a file called card.raw

The pictures were stored in JPEG format. JPEGs  have “signatures,” patterns of bytes that can distinguish them from other file formats. Specifically, the first three bytes of JPEGs are

0xff 0xd8 0xff.
