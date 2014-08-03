# Require any additional compass plugins here.

#Folder settings
relative_assets = true      #because we're not working from the root
css_dir = "../css"          #where the CSS will saved
sass_dir = "sass"           #where our .scss files are
images_dir = "../images"    #the folder with your images
additional_import_paths = ["/var/lib/gems/1.9.1/gems/zen-grids-1.4/stylesheets"]

# You can select your preferred output style here (can be overridden via the command line):
output_style = :expanded # After dev :compressed

# To disable debugging comments that display the original location of your selectors. Uncomment:
line_comments = true

# Obviously
preferred_syntax = :scss